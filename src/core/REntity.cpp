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
#include "RBlockReferenceEntity.h"
#include "RDocument.h"
#include "REntity.h"
#include "RExplodable.h"
#include "RShape.h"
#include "RSpline.h"

RPropertyTypeId REntity::PropertyCustom;
RPropertyTypeId REntity::PropertyHandle;
RPropertyTypeId REntity::PropertyType;
RPropertyTypeId REntity::PropertyBlock;
RPropertyTypeId REntity::PropertyLayer;
RPropertyTypeId REntity::PropertyLinetype;
RPropertyTypeId REntity::PropertyLineweight;
RPropertyTypeId REntity::PropertyColor;
RPropertyTypeId REntity::PropertyDrawOrder;

RPropertyTypeId REntity::PropertyMinX;
RPropertyTypeId REntity::PropertyMaxX;
RPropertyTypeId REntity::PropertyMinY;
RPropertyTypeId REntity::PropertyMaxY;


REntity::~REntity() {
}

void REntity::init() {
    REntity::PropertyCustom.generateId(typeid(REntity), RObject::PropertyCustom);
    REntity::PropertyHandle.generateId(typeid(REntity), RObject::PropertyHandle);
    REntity::PropertyType.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Type"));
    REntity::PropertyBlock.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Block ID"));
    REntity::PropertyLayer.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Layer"));
    REntity::PropertyLinetype.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Linetype"));
    REntity::PropertyLineweight.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Lineweight"));
    REntity::PropertyColor.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Color"));
    REntity::PropertyDrawOrder.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Draw Order"));

    REntity::PropertyMinX.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Left"));
    REntity::PropertyMinY.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Bottom"));
    REntity::PropertyMaxX.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Right"));
    REntity::PropertyMaxY.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Top"));
}

/**
 * \copydoc REntityData::getLineweight
 */
RLineweight::Lineweight REntity::getLineweight(bool resolve,
    const QStack<REntity*>& blockRefStack) const {

    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }

    return getData().getLineweight(resolve, newBlockRefStack);
}

/**
 * \copydoc REntityData::getColor
 */
RColor REntity::getColor(bool resolve, const QStack<REntity*>& blockRefStack) {

    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }

    return getData().getColor(resolve, newBlockRefStack);
}

/**
 * \copydoc REntityData::getLineweightInUnits
 */
double REntity::getLineweightInUnits(const QStack<REntity*>& blockRefStack) const {
    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }
    return getData().getLineweightInUnits(newBlockRefStack);
}

/**
 * \copydoc REntityData::getLinetypeId
 */
RLinetype::Id REntity::getLinetypeId(bool resolve, const QStack<REntity*>& blockRefStack) const {
    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }
    return getData().getLinetypeId(resolve, newBlockRefStack);
}

/**
 * Copies all attributes (layer, block, color, line weight, line style) from the given entity.
 */
void REntity::copyAttributesFrom(REntity* entity, bool copyBlockId) {
    if (entity==NULL) {
        qWarning("REntity::copyAttributesFrom: source entity is NULL");
        return;
    }

    if (getDocument()!=entity->getDocument()) {
        qWarning("REntity::copyAttributesFrom: source entity not from same document");
        //RDebug::printBacktrace();
        return;
    }

    setLayerId(entity->getLayerId());
    if (copyBlockId) {
        setBlockId(entity->getBlockId());
    }
    setColor(entity->getColor());
    setLineweight(entity->getLineweight());
    setLinetypeId(entity->getLinetypeId());
}

QList<RVector> REntity::getIntersectionPoints(
        const REntity& other, bool limited, const RBox& queryBox) const {

    bool same = false;

    // avoid intersection finding for intersections of interpolated entities
    // (e.g. splines) with themselves:
    if (getId()!=INVALID_ID && getId()==other.getId() && getDocument()==other.getDocument()) {
        const RShape* shape = getData().castToConstShape();
        if (shape!=NULL && shape->isInterpolated()) {
            same = true;
        }

        const RPolyline* pl = dynamic_cast<const RPolyline*>(shape);
        if (pl!=NULL) {
            same = true;
        }
    }

    return getData().getIntersectionPoints(other.getData(), limited, same, queryBox/*, pos, posOther*/);
}

QList<RVector> REntity::getIntersectionPoints(const RShape& shape, bool limited, const RBox& queryBox) const {
    return getData().getIntersectionPoints(shape, limited, queryBox);
}

QPair<QVariant, RPropertyAttributes> REntity::getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyType) {
        return qMakePair(QVariant(getType()), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyBlock) {
        return qMakePair(QVariant(getData().getBlockId()),
                         RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyLayer) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
                if (!noAttributes) {
                    // TODO: filter out locked layers:
                    attr.setChoices(document->getLayerNames());
                }
                return qMakePair(QVariant(document->getLayerName(
                        getData().getLayerId())), attr);
            }
        }
        else {
            return qMakePair(QVariant(getData().getLayerId()),
                    RPropertyAttributes());
        }
    }
    else if (propertyTypeId == PropertyLinetype) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                QVariant var;
                QSharedPointer<RLinetype> linetype = document->queryLinetype(
                        getData().getLinetypeId());
                var.setValue<RLinetype> (*linetype.data());
                return qMakePair(var, RPropertyAttributes());
            }
        }
        else {
            return qMakePair(QVariant(getData().getLinetypeId()),
                    RPropertyAttributes());
        }
    }
    else if (propertyTypeId == PropertyLineweight) {
        QVariant v;
        v.setValue<RLineweight::Lineweight>(getData().getLineweight());
        return qMakePair(v, RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyColor) {
        QVariant var;
        var.setValue<RColor> (getData().getColor());
        return qMakePair(var, RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyDrawOrder) {
        return qMakePair(QVariant(getData().getDrawOrder()), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyMinX) {
        return qMakePair(QVariant(getBoundingBox().getMinimum().x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId == PropertyMinY) {
        return qMakePair(QVariant(getBoundingBox().getMinimum().y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId == PropertyMaxX) {
        return qMakePair(QVariant(getBoundingBox().getMaximum().x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }
    else if (propertyTypeId == PropertyMaxY) {
        return qMakePair(QVariant(getBoundingBox().getMaximum().y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool REntity::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {

    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    if (propertyTypeId == PropertyBlock) {
        ret = ret || RObject::setMember(getData().blockId, value.toInt(), true);
    } else if (propertyTypeId == PropertyLayer) {
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            ret = ret || RObject::setMember(getData().layerId, value.toInt(), true);
        } else if (value.type() == QVariant::String) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                ret = ret || RObject::setMember(getData().layerId,
                        document->getLayerId(value.toString()), true);
            }
        }
    } else if (propertyTypeId == PropertyLinetype) {
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            ret = ret || RObject::setMember(getData().linetypeId, value.toInt(), true);
        } else {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RLinetype t = value.value<RLinetype> ();
                int id = document->getLinetypeId(t.getName());
                ret = ret || RObject::setMember(getData().linetypeId, id,
                        true);
            }
        }
    } else if (propertyTypeId == PropertyLineweight) {
        if (value.type()==QVariant::Int || value.type()==QVariant::Double) {
            ret = ret || RObject::setMember((int&)getData().lineweight,
                value.value<int>(), true);
        }
        else {
            ret = ret || RObject::setMember((int&)getData().lineweight,
                (int)value.value<RLineweight::Lineweight>(), true);
        }
    } else if (propertyTypeId == PropertyColor) {
        ret = ret || RObject::setMember(getData().color, value, true);
    } else if (propertyTypeId == PropertyDrawOrder) {
        ret = ret || RObject::setMember(getData().drawOrder, value, true);
    }

    return ret;
}

/**
 * \return true if this entity is visible (i.e. is not on a frozen layer
 * or in a frozen block).
 */
bool REntity::isVisible() const {
    if (getDocument()==NULL) {
        return true;
    }

    // check if layer is frozen:
    if (getDocument()->isLayerFrozen(getLayerId())) {
        return false;
    }

    // check if block is frozen:
    const RBlockReferenceEntity* blockRef = dynamic_cast<const RBlockReferenceEntity*>(this);
    if (blockRef!=NULL) {
        RBlock::Id blockId = blockRef->getReferencedBlockId();
        if (blockId!=RBlock::INVALID_ID) {
            QSharedPointer<RBlock> block = getDocument()->queryBlockDirect(blockId);
            if (!block.isNull() && block->isFrozen()) {
                return false;
            }
        }
    }

    return true;
}

/**
 * \return true if this entity can be edited (i.e. is not on a locked layer).
 */
bool REntity::isEditable(bool allowInvisible) const {
    if (getDocument()==NULL) {
        return true;
    }

    // entities that are not visible are never editable:
    if (!allowInvisible && !isVisible()) {
        return false;
    }

    // entities on locked layers are not editable:
    if (getDocument()->isLayerLocked(getLayerId())) {
        return false;
    }

    return true;
}

/**
 * \copydoc REntityData::setSelected
 */
void REntity::setSelected(bool on) {
    getData().setSelected(on);
}

/**
 * Stream operator for QDebug
 */
void REntity::print(QDebug dbg) const {
    dbg.nospace() << "REntity(";
    RObject::print(dbg);
    dbg.nospace() 
        << ", type: " << getType()
        << ", layerId: " << getLayerId()
        << ", blockId: " << getBlockId()
        << ", parentId: " << getParentId()
        << ", childIds: " << getDocument()->queryChildEntities(getId())
        << ", lineweight: " << getLineweight()
        << ", linetypeId: " << getLinetypeId()
        << ", color: " << getColor()
        << ", drawOrder: " << getDrawOrder()
        << ", selectionStatus: " << isSelected()
        << ", boundingBoxes: " << getBoundingBoxes()
        << ")";
}

void REntity::dump() {
    qDebug() << *this;
}
