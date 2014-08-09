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
#include "RXLineEntity.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RXLineEntity::PropertyCustom;
RPropertyTypeId RXLineEntity::PropertyHandle;
RPropertyTypeId RXLineEntity::PropertyType;
RPropertyTypeId RXLineEntity::PropertyBlock;
RPropertyTypeId RXLineEntity::PropertyLayer;
RPropertyTypeId RXLineEntity::PropertyLinetype;
RPropertyTypeId RXLineEntity::PropertyLineweight;
RPropertyTypeId RXLineEntity::PropertyColor;
RPropertyTypeId RXLineEntity::PropertyDrawOrder;

RPropertyTypeId RXLineEntity::PropertyBasePointX;
RPropertyTypeId RXLineEntity::PropertyBasePointY;
RPropertyTypeId RXLineEntity::PropertyBasePointZ;
RPropertyTypeId RXLineEntity::PropertySecondPointX;
RPropertyTypeId RXLineEntity::PropertySecondPointY;
RPropertyTypeId RXLineEntity::PropertySecondPointZ;

RPropertyTypeId RXLineEntity::PropertyDirectionX;
RPropertyTypeId RXLineEntity::PropertyDirectionY;
RPropertyTypeId RXLineEntity::PropertyDirectionZ;

RPropertyTypeId RXLineEntity::PropertyAngle;


RXLineEntity::RXLineEntity(RDocument* document, const RXLineData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
}

RXLineEntity::~RXLineEntity() {
}

void RXLineEntity::setShape(const RXLine& l) {
    data.setBasePoint(l.getBasePoint());
    data.setSecondPoint(l.getSecondPoint());
}

void RXLineEntity::init() {
    RXLineEntity::PropertyCustom.generateId(typeid(RXLineEntity), RObject::PropertyCustom);
    RXLineEntity::PropertyHandle.generateId(typeid(RXLineEntity), RObject::PropertyHandle);
    RXLineEntity::PropertyType.generateId(typeid(RXLineEntity), REntity::PropertyType);
    RXLineEntity::PropertyBlock.generateId(typeid(RXLineEntity), REntity::PropertyBlock);
    RXLineEntity::PropertyLayer.generateId(typeid(RXLineEntity), REntity::PropertyLayer);
    RXLineEntity::PropertyLinetype.generateId(typeid(RXLineEntity), REntity::PropertyLinetype);
    RXLineEntity::PropertyLineweight.generateId(typeid(RXLineEntity), REntity::PropertyLineweight);
    RXLineEntity::PropertyColor.generateId(typeid(RXLineEntity), REntity::PropertyColor);
    RXLineEntity::PropertyDrawOrder.generateId(typeid(RXLineEntity), REntity::PropertyDrawOrder);

    RXLineEntity::PropertyBasePointX.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Base Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RXLineEntity::PropertyBasePointY.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Base Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RXLineEntity::PropertyBasePointZ.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Base Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RXLineEntity::PropertySecondPointX.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Second Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RXLineEntity::PropertySecondPointY.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Second Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RXLineEntity::PropertySecondPointZ.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Second Point"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RXLineEntity::PropertyDirectionX.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Direction Vector"), QT_TRANSLATE_NOOP("REntity", "X"));
    RXLineEntity::PropertyDirectionY.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Direction Vector"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RXLineEntity::PropertyDirectionZ.generateId(typeid(RXLineEntity), QT_TRANSLATE_NOOP("REntity", "Direction Vector"), QT_TRANSLATE_NOOP("REntity", "Z"));

    RXLineEntity::PropertyAngle.generateId(typeid(RXLineEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
}

bool RXLineEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value);

    ret = ret || RObject::setMember(data.basePoint.x, value, PropertyBasePointX == propertyTypeId);
    ret = ret || RObject::setMember(data.basePoint.y, value, PropertyBasePointY == propertyTypeId);
    ret = ret || RObject::setMember(data.basePoint.z, value, PropertyBasePointZ == propertyTypeId);
    ret = ret || RObject::setMember(data.directionVector.x, value, PropertyDirectionX == propertyTypeId);
    ret = ret || RObject::setMember(data.directionVector.y, value, PropertyDirectionY == propertyTypeId);
    ret = ret || RObject::setMember(data.directionVector.z, value, PropertyDirectionZ == propertyTypeId);

    if (propertyTypeId == PropertySecondPointX) {
        RVector v = data.getSecondPoint();
        v.x = value.toDouble();
        data.setSecondPoint(v);
        ret = true;
    } else if (propertyTypeId == PropertySecondPointY) {
        RVector v = data.getSecondPoint();
        v.y = value.toDouble();
        data.setSecondPoint(v);
        ret = true;
    } else if (propertyTypeId == PropertySecondPointZ) {
        RVector v = data.getSecondPoint();
        v.z = value.toDouble();
        data.setSecondPoint(v);
        ret = true;
    }

    else if (propertyTypeId==PropertyAngle) {
        data.setAngle(value.toDouble());
        ret = true;
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RXLineEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes) {
    if (propertyTypeId == PropertyBasePointX) {
        return qMakePair(QVariant(data.basePoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBasePointY) {
        return qMakePair(QVariant(data.basePoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBasePointZ) {
        return qMakePair(QVariant(data.basePoint.z), RPropertyAttributes());
    }

    else if (propertyTypeId == PropertySecondPointX) {
        return qMakePair(QVariant(data.getSecondPoint().x), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertySecondPointY) {
        return qMakePair(QVariant(data.getSecondPoint().y), RPropertyAttributes(RPropertyAttributes::Redundant));
    } else if (propertyTypeId == PropertySecondPointZ) {
        return qMakePair(QVariant(data.getSecondPoint().z), RPropertyAttributes(RPropertyAttributes::Redundant));
    }

    else if (propertyTypeId == PropertyDirectionX) {
        return qMakePair(QVariant(data.getDirectionVector().x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionY) {
        return qMakePair(QVariant(data.getDirectionVector().y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionZ) {
        return qMakePair(QVariant(data.getDirectionVector().z), RPropertyAttributes());
    }

    if (propertyTypeId==PropertyAngle) {
        return qMakePair(QVariant(data.getAngle()), RPropertyAttributes(RPropertyAttributes::Angle|RPropertyAttributes::Redundant));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RXLineEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview);

    e.setBrush(Qt::NoBrush);
    e.exportXLine(data);
}

void RXLineEntity::print(QDebug dbg) const {
    dbg.nospace() << "RXLineEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", startPoint: " << getBasePoint() << ", endPoint: "
            << getDirectionVector() << ")";
}
