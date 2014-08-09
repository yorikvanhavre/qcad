/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include "RDocument.h"
#include "REntity.h"
#include "REntityData.h"
#include "RExplodable.h"
#include "RBlockReferenceEntity.h"

REntityData::REntityData(RDocument* document) :
    document(document),
    selectionStatus(false), 
    drawOrder(0), 
    layerId(RLayer::INVALID_ID), 
    blockId(RBlock::INVALID_ID), 
    parentId(REntity::INVALID_ID),
    linetypeId(RLinetype::INVALID_ID),
    lineweight(RLineweight::WeightInvalid),
    color() {

}

QString REntityData::getLayerName() const {
    if (getDocument()==NULL) {
        qWarning("REntityData::getLayerName: document is NULL");
        return QString();
    }
    return getDocument()->getLayerName(layerId);
}

QString REntityData::getBlockName() const {
    if (getDocument()==NULL) {
        qWarning("REntityData::getBlockName: document is NULL");
        return QString();
    }
    return getDocument()->getBlockName(blockId);
}

// TODO: fix
double REntityData::getLineweightInUnits(const QStack<REntity*>& blockRefStack) const {
    RLineweight::Lineweight lw = getLineweight(true, blockRefStack);
    // TODO: unit conversion:
    return lw / 100.0;
}

/**
 * \return Color of this entity.
 *
 * \param resolve Resolve color if ByLayer or ByBlock.
 */
RColor REntityData::getColor(bool resolve, const QStack<REntity*>& blockRefStack) const {

    if (!resolve) {
        return getColor();
    }

    if (color.isByLayer()) {
        if (document==NULL) {
            qWarning() << "REntityData::getColor: "
                          "color is ByLayer but layer is NULL "
                          "and document is NULL";
            return RColor(Qt::white);
        }
        QSharedPointer<RLayer> l = document->queryLayerDirect(layerId);
        if (l.isNull()) {
            qWarning() << "REntityData::getColor: "
                          "color is ByLayer but layer is invalid";
            return RColor(Qt::white);
        }
        return l->getColor();
    }

    if (color.isByBlock()) {
        if (blockRefStack.isEmpty()) {
            return RColor(Qt::white);
        }
        return blockRefStack.top()->getColor(true, blockRefStack);
    }

    return getColor();
}

/**
 * \param resolve True: resolve ByLayer / ByBlock and always return a
 *      lineweight in 1/100 mm.
 * \param layer Layer to use for resolving if known, NULL otherwise.
 * \param blockRef Block reference to use for resolving if known,
 *      NULL otherwise.
 */
RLineweight::Lineweight REntityData::getLineweight(bool resolve, const QStack<REntity*>& blockRefStack) const {

    if (!resolve) {
        return getLineweight();
    }

    RLineweight::Lineweight lw = lineweight;

    if (lineweight==RLineweight::WeightByLayer) {
        const RDocument* doc = getDocument();
        if (doc==NULL) {
            qWarning() << "REntityData::getLineweight: "
                          "line weight is ByLayer but layer is NULL "
                          "and document is NULL";
            return RLineweight::Weight000;
        }
        QSharedPointer<RLayer> l = doc->queryLayerDirect(layerId);
        if (l.isNull()) {
            qWarning() << "REntityData::getLineweight: "
                          "line weight is ByLayer but layer is invalid";
            return RLineweight::Weight000;
        }
        lw = l->getLineweight();
        if (lw==RLineweight::WeightByLayer) {
            qWarning() << "REntityData::getLineweight: "
                          "line weight of layer '" << l->getName() << "' is ByLayer";
            return RLineweight::Weight000;
        }
    }
    else if (lineweight==RLineweight::WeightByBlock) {
        if (blockRefStack.isEmpty()) {
            return RLineweight::Weight000;
        }
        lw = blockRefStack.top()->getLineweight(true, blockRefStack);
    }

    if (lw==RLineweight::WeightByLwDefault) {
        // TODO: return default line weight:
        lw = RLineweight::Weight000;
    }

    if (lw==RLineweight::WeightInvalid) {
        // TODO: return default line weight:
        lw = RLineweight::Weight000;
    }

    if (lw<0) {
        qWarning() << "REntityData::getLineweight: not resolved: " << lw;
    }

    return lw;
}

RLinetype::Id REntityData::getLinetypeId(bool resolve, const QStack<REntity*>& blockRefStack) const {

    if (!resolve) {
        return getLinetypeId();
    }

    if (document!=NULL) {
        if (document->isByLayer(linetypeId)) {
            QSharedPointer<RLayer> l = document->queryLayerDirect(layerId);
            if (l.isNull()) {
                qWarning() << "REntityData::getLinetypeId: "
                              "line type is ByLayer but layer is invalid";
                return RLinetype::INVALID_ID;
            }
            return l->getLinetypeId();
        }

        else if (document->isByBlock(linetypeId)) {
            if (blockRefStack.isEmpty()) {
//                qWarning() << "REntityData::getColor: "
//                              "color is ByBlock but entity not in block reference";
                return RLinetype::INVALID_ID;
            }
            return blockRefStack.top()->getLinetypeId(true, blockRefStack);
        }
    }

    return getLinetypeId();
}


/**
 * \return The shortest distance from this entity to the given point.
 */
double REntityData::getDistanceTo(const RVector& point, bool limited, double range, bool draft) const {
    Q_UNUSED(range);
    Q_UNUSED(draft);

    RVector v = getVectorTo(point, limited);
    if (v.isValid()) {
        return v.getMagnitude();
    }
    return RNANDOUBLE;
}


void REntityData::setLinetype(RLinetype linetype) {
    if (document!=NULL) {
        this->linetypeId = document->getLinetypeId(linetype.getName());
    }
}

/**
 * \return The bounding box that contains this entity.
 */
RBox REntityData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    RBox bb;
    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        if (!bb.isValid()) {
            bb = shapes.at(i)->getBoundingBox();
        }
        else {
            bb.growToInclude(shapes.at(i)->getBoundingBox());
        }
    }
    return bb;
}

/**
 * \return A point that is on the entity. Used to check if an entity is
 *  inside a polygon.
 */
RVector REntityData::getPointOnEntity() const {
    QList<RVector> endPoints = getEndPoints();
    if (endPoints.size()>0) {
        return endPoints[0];
    }
    else {
        return getClosestPointOnEntity(RVector(0.0,0.0));
    }
}

/**
 * \return Vector of end points of this entity. Used for snap to end points.
 */
QList<RVector> REntityData::getEndPoints(const RBox& queryBox) const {
    QList<RVector> ret;
    QList<QSharedPointer<RShape> > shapes = getShapes(queryBox);
    for (int i=0; i<shapes.size(); i++) {
        ret.append(shapes.at(i)->getEndPoints());
    }
    return ret;
}

/**
 * \return Vector of middle points of this entity. Used for snap to
 *        middle points.
 */
QList<RVector> REntityData::getMiddlePoints(const RBox& queryBox) const {
    QList<RVector> ret;
    QList<QSharedPointer<RShape> > shapes = getShapes(queryBox);
    for (int i=0; i<shapes.size(); i++) {
        ret.append(shapes.at(i)->getMiddlePoints());
    }
    return ret;
}

/**
 * \return Vector of center points of this entity. Used for snap to
 *        center points.
 */
QList<RVector> REntityData::getCenterPoints(const RBox& queryBox) const {
    QList<RVector> ret;
    QList<QSharedPointer<RShape> > shapes = getShapes(queryBox);
    for (int i=0; i<shapes.size(); i++) {
        ret.append(shapes.at(i)->getCenterPoints());
    }
    return ret;
}

/**
 * \return Points on entity with given \c distance to either endpoint.
 * Used for snap to points with distance on entity.
 */
QList<RVector> REntityData::getPointsWithDistanceToEnd(double distance, RS::From from, const RBox& queryBox) const {
    QList<RVector> ret;
    QList<QSharedPointer<RShape> > shapes = getShapes(queryBox);
    for (int i=0; i<shapes.size(); i++) {
        ret.append(shapes.at(i)->getPointsWithDistanceToEnd(distance, from));
    }
    return ret;
}

/**
 * \return Closest point to \c point on this entity. Used for snap to
 *        points on entity.
 */
RVector REntityData::getClosestPointOnEntity(const RVector& point,
    double range, bool limited) const {

    Q_UNUSED(range)

    RVector ret = RVector::invalid;
    double minDist = RMAXDOUBLE;
    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        RVector r = shapes.at(i)->getClosestPointOnShape(point, limited);
        double dist = r.getDistanceTo(point);
        if (!ret.isValid() || dist<minDist) {
            ret = r;
            minDist = dist;
        }
    }
    return ret;
}


/**
 * \return The distance vector from this entity to the given point.
 *
 * \param point the point to which the distance was measured
 *
 * \param limited: If true, an invalid vector is returned if the
 *   closest point on the entity is outside of the entity (e.g. in
 *   the extension line of a line or outside the start / end angle
 *   of an arc).
 */
RVector REntityData::getVectorTo(const RVector& point, bool limited) const {
    RVector ret = RVector::invalid;
    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        shapes.at(i)->to2D();
        RVector r = shapes.at(i)->getVectorTo(point, limited);
        if (!ret.isValid() || r.getMagnitude()<ret.getMagnitude()) {
            ret = r;
        }
    }
    return ret;
}

/**
 * \return True if the given point is on this entity.
 */
bool REntityData::isOnEntity(const RVector& point, bool limited) const {
    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        if (shapes.at(i)->isOnShape(point, limited)) {
            return true;
        }
    }
    return false;
}

/**
 * \return True if this entity intersects with the given shape,
 *      false otherwise.
 * \todo better to pass another entity data object?
 */
bool REntityData::intersectsWith(const RShape& shape) const {
    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        if (shapes.at(i)==NULL) {
            qWarning() << "REntityData::intersectsWith: ignoring NULL shape";
            continue;
        }
        if (shapes.at(i)->intersectsWith(shape)) {
            return true;
        }
    }
    return false;
}

/**
 * \return Points on entity which are intersection points with the
 *     given other entity. If \c same is true, the two datas originate
 *     from the same entity.
 */
QList<RVector> REntityData::getIntersectionPoints(
        const REntityData& other, bool limited, bool same, const RBox& queryBox) const {

    QList<RVector> ret;
    QList<QSharedPointer<RShape> > shapes1 = getShapes(queryBox);
    QList<QSharedPointer<RShape> > shapes2 = other.getShapes(queryBox);

    for (int i=0; i<shapes1.size(); i++) {
        for (int k=0; k<shapes2.size(); k++) {
            ret.append(
                shapes1.at(i)->getIntersectionPoints(*shapes2.at(k), limited, same)
            );
        }
    }

    return ret;
}

/**
 * \return Points on entity which are intersection points with the
 *     given shape.
 */
QList<RVector> REntityData::getIntersectionPoints(const RShape& shape, bool limited, const RBox& queryBox) const {
    QList<RVector> ret;
    QList<QSharedPointer<RShape> > shapes1 = getShapes(queryBox);
    for (int i=0; i<shapes1.size(); i++) {
        ret.append(shapes1.at(i)->getIntersectionPoints(shape, limited));
    }
    return ret;
}

/**
 * Moves this entity by the given offset.
 */
bool REntityData::move(const RVector& offset) {
    // if this entity is based on a shape (point,line,arc,...),
    // transform using shape API:
    RShape* s = castToShape();
    if (s==NULL) {
        return false;
    }
    return s->move(offset);
}

bool REntityData::rotate(double rotation, const RVector& center) {
    // if this entity is based on a shape (point,line,arc,...),
    // transform using shape API:
    RShape* s = castToShape();
    if (s==NULL) {
        return false;
    }
    return s->rotate(rotation, center);
}

bool REntityData::scale(const RVector& scaleFactors, const RVector& center) {
    // if this entity is based on a shape (point,line,arc,...),
    // transform using shape API:
    RShape* s = castToShape();
    if (s==NULL) {
        return false;
    }
    return s->scale(scaleFactors, center);
}

bool REntityData::scale(double scaleFactor, const RVector& center) {
    return scale(RVector(scaleFactor, scaleFactor, scaleFactor), center);
}

bool REntityData::mirror(const RLine& axis) {
    // if this entity is based on a shape (point,line,arc,...),
    // transform using shape API:
    RShape* s = castToShape();
    if (s==NULL) {
        return false;
    }
    return s->mirror(axis);
}

bool REntityData::mirror(const RVector& axis1, const RVector& axis2) {
    return mirror(RLine(axis1, axis2));
}

bool REntityData::flipHorizontal() {
    return mirror(RLine(RVector(0,0), RVector(0,1)));
}

bool REntityData::flipVertical() {
    return mirror(RLine(RVector(0,0), RVector(1,0)));
}

/**
 * Stretches the end points of this entity that are inside area by offset.
 */
bool REntityData::stretch(const RPolyline& area, const RVector& offset) {
    // if this entity is based on a shape (point,line,arc,...),
    // transform using shape API:
    RShape* s = castToShape();
    if (s==NULL) {
        return false;
    }
    return s->stretch(area, offset);
}

/**
 * \return The one shape that is part of this entity which is the
 *      closest to the given position.
 */
QSharedPointer<RShape> REntityData::getClosestShape(const RVector& pos, double range) const {
    QSharedPointer<RShape> ret;

    QList<QSharedPointer<RShape> > shapes;
    if (RMath::isNaN(range)) {
        shapes = getShapes();
    }
    else {
        shapes = getShapes(RBox(pos, range));
    }

    // entity not based on shape:
    if (shapes.size()==0) {
        return ret;
    }

    // entity based on one or more shapes, find closest:
    double minDistance = RMAXDOUBLE;
    QList<QSharedPointer<RShape> >::const_iterator it;
    for (it=shapes.constBegin(); it!=shapes.constEnd(); ++it) {
        QSharedPointer<RShape> shape = (*it);

        // explode shape if possible:
        QList<QSharedPointer<RShape> > subShapes;
        QSharedPointer<RExplodable> explodable = shape.dynamicCast<RExplodable>();
        // 20110916: interpolated shapes are not exploded at this point (e.g.
        // for perpendicular snap to spline inside block):
        if (explodable.isNull() || shape->isInterpolated()) {
            subShapes.append(QSharedPointer<RShape>(shape->clone()));
        }
        else {
            subShapes = explodable->getExploded();
        }

        QList<QSharedPointer<RShape> >::iterator it2;
        for (it2=subShapes.begin(); it2!=subShapes.end(); ++it2) {
            QSharedPointer<RShape> shape2 = (*it2);
            double distance = shape2->getDistanceTo(pos);
            if (distance<minDistance) {
                minDistance = distance;
                ret = shape2;
            }
        }
    }

    return ret;
}
