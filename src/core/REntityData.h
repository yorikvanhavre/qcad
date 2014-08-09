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

#ifndef RENTITYDATA_H
#define RENTITYDATA_H

#include "core_global.h"

#include <QList>
#include <QStack>

#include "RBlock.h"
#include "RBox.h"
#include "RColor.h"
#include "RLayer.h"
#include "RLine.h"
#include "RMatrix.h"
#include "RObject.h"
#include "RPolyline.h"
#include "RView.h"

class RBlockReferenceEntity;
class RDocument;
class REntity;
class RExporter;

#ifndef RDEFAULT_QSET_INT
#define RDEFAULT_QSET_INT QSet<int>()
#endif

/**
 * Base class for all entity data classes. Such classes are
 * used to separate functionality from data. Data objects may
 * for example be used to perform certain calculations. A
 * custom entity might use the same data class as a standard
 * entity to provide similar behavior (e.g. a wall might
 * behave similar like a line entity).
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup core
 */
class QCADCORE_EXPORT REntityData {

    friend class REntity;

public:
    REntityData(RDocument* document=NULL);

    virtual ~REntityData() {}

    RDocument* getDocument() {
        return document;
    }

    const RDocument* getDocument() const {
        return document;
    }

    void setDocument(RDocument* document) {
        this->document = document;
    }

    /**
     * \return Shapes that represent the geometry of this entity.
     */
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox)

        return QList<QSharedPointer<RShape> >();
    }

    /**
     * \return The one shape that is part of this entity which is the
     *      closest to the given position.
     */
    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE) const;

    virtual RShape* castToShape() {
        return NULL;
    }

    /**
     * \nonscriptable
     */
    virtual const RShape* castToConstShape() const {
        return const_cast<REntityData*>(this)->castToShape();
    }

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    /**
     * \return Vector of bounding boxes that contain this entity.
     * This is used for complex entities such as block references
     * to further optimize algorithms that depend on bounding boxes
     * (e.g. spatial index algorithms). The default implementation
     * returns the bounding box that contains the whole entity.
     */
    virtual QList<RBox> getBoundingBoxes(bool ignoreEmpty=false) const {
        return QList<RBox>() << getBoundingBox(ignoreEmpty);
    }

    /**
     * \return True if the entity is currently selected. This can for example
     *      influence the color in which the entity is exported.
     */
    virtual bool isSelected() const {
        return selectionStatus;
    }

    /**
     * Selects or deselects this entity.
     */
    virtual void setSelected(bool on) {
        selectionStatus = on;
    }

    /**
     * \return The draw order of this entity. Entities are usually drawn in
     * ascending order of this number.
     */
    virtual int getDrawOrder() const {
        return drawOrder;
    }

    /**
     * Sets the draw order of this entity.
     */
    virtual void setDrawOrder(int drawOrder) {
        this->drawOrder = drawOrder;
    }

    virtual void setLayerId(RLayer::Id layerId) {
        this->layerId = layerId;
    }

    RLayer::Id getLayerId() const {
        return layerId;
    }

    QString getLayerName() const;

    virtual void setBlockId(RBlock::Id blockId) {
        this->blockId = blockId;
    }

    RBlock::Id getBlockId() const {
        return blockId;
    }

    virtual void setParentId(RObject::Id parentId) {
        this->parentId = parentId;
    }

    RObject::Id getParentId() const {
        return parentId;
    }

    QString getBlockName() const;

    virtual void setLinetypeId(RLinetype::Id linetypeId) {
        this->linetypeId = linetypeId;
    }

    virtual void setLinetype(RLinetype linetype);

    RLinetype::Id getLinetypeId() const {
        return linetypeId;
    }

    virtual RLinetype::Id getLinetypeId(bool resolve,
        const QStack<REntity*>& blockRefStack) const;

    RLineweight::Lineweight getLineweight() const {
        return lineweight;
    }

    virtual RLineweight::Lineweight getLineweight(bool resolve,
        const QStack<REntity*>& blockRefStack) const;

    double getLineweightInUnits(const QStack<REntity*>& blockRefStack) const;

    void setLineweight(RLineweight::Lineweight lineweight) {
        this->lineweight = lineweight;
    }

    void setColor(const RColor& color) {
        this->color = color;
    }

    virtual RColor getColor() const {
        return color;
    }

    virtual RColor getColor(bool resolve, const QStack<REntity *>& blockRefStack) const;

    /**
     * Can be overwritten to return internal, resolved reference points.
     * This is used for example for block references in combination with
     * snap to reference points.
     * Default implementation returns same as getReferencePoints().
     */
    virtual QList<RVector> getInternalReferencePoints(
        RS::ProjectionRenderingHint hint=RS::RenderTop) const {

        Q_UNUSED(hint)

        return getReferencePoints();
    }

    /**
     * \return Vector of reference points of this entity. Reference points
     *      can usually be moved around by the user to change the geometry
     *      of the entity.
     */
    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint=RS::RenderTop) const = 0;

    virtual RVector getPointOnEntity() const;
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getMiddlePoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getCenterPoints(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny, const RBox& queryBox = RDEFAULT_RBOX) const;

    virtual RVector getClosestPointOnEntity(const RVector& point,
        double range=RNANDOUBLE, bool limited=true) const;

//    /**
//     * Override to disable intersection point
//     */
//    virtual bool intersectionsEnabled() {
//        return true;
//    }

    virtual QList<RVector> getIntersectionPoints(
            const REntityData& other, bool limited = true, bool same = false,
            const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<RVector> getIntersectionPoints(
            const RShape& shape, bool limited = true,
            const RBox& queryBox = RDEFAULT_RBOX) const;

    virtual RVector getVectorTo(const RVector& point, bool limited=true) const;

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false) const;

    /**
     * \return True if this entity is completely inside the given box,
     *     false otherwise. Only geometry is accounted for, not the line width.
     */
    virtual bool isInside(const RBox& box) const {
        return box.contains(getBoundingBox());
    }

    virtual bool isOnEntity(const RVector& point, bool limited = true) const;

    virtual bool intersectsWith(const RShape& shape) const;

    /**
     * Moves the given reference point to the given target point or does nothing
     * if this entity has no reference point as the given location.
     *
     * \return True if a reference point has been moved successfully,
     *        false otherwise.
     */
    virtual bool moveReferencePoint(
        const RVector& referencePoint, const RVector& targetPoint
    ) = 0;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(double scaleFactor, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool mirror(const RVector& axis1, const RVector& axis2);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    /**
     * Entities can reimplement this function to invalidate any internal cache
     * (mark the entity as dirty).
     */
    virtual void update() const {}

protected:
    RDocument* document;
    bool selectionStatus;
    int drawOrder;
    RLayer::Id layerId;
    RBlock::Id blockId;
    RObject::Id parentId;
    RLinetype::Id linetypeId;
    RLineweight::Lineweight lineweight;
    RColor color;
};

Q_DECLARE_METATYPE(REntityData*)
Q_DECLARE_METATYPE(const REntityData*)
Q_DECLARE_METATYPE(QSharedPointer<REntityData>)
Q_DECLARE_METATYPE(QSharedPointer<REntityData>*)

#endif
