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

#ifndef RVIEWPORTDATA_H
#define RVIEWPORTDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RLine.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a viewport entity.
 *
 * \scriptable
 * \ingroup core
 */
class QCADCORE_EXPORT RViewportData: public REntityData {

    friend class RViewportEntity;

protected:
    RViewportData(RDocument* document, const RViewportData& data);

public:
    RViewportData();
//    RViewportData(const RVector& center, double width, double height, double scale,
//        const RVector& viewCenter,
//        const RVector& viewTarget);

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    int getViewportId() const {
       return viewportId;
    }

    void setViewportId(int id) {
        viewportId = id;
    }

    int getStatus() const {
        return status;
    }

    void setStatus(int s) {
        status = s;
    }

    RVector getCenter() const {
       return center;
    }

    void setCenter(const RVector& c) {
        center = c;
    }

    RVector getViewCenter() const {
       return viewCenter;
    }

    void setViewCenter(const RVector& c) {
        viewCenter = c;
    }

    RVector getViewTarget() const {
        return viewTarget;
    }

    void setViewTarget(const RVector& t) {
        viewTarget = t;
    }

    double getWidth() const {
        return width;
    }

    void setWidth(double w) {
        width = w;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double h) {
        height = h;
    }

    double getScale() const {
        return scale;
    }

    void setScale(double s) {
        scale = s;
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;

private:
    int viewportId;
    int status;
    RVector center;
    double width;
    double height;
    double scale;

    RVector viewCenter;
    RVector viewTarget;
};

Q_DECLARE_METATYPE(RViewportData*)
Q_DECLARE_METATYPE(const RViewportData*)
Q_DECLARE_METATYPE(QSharedPointer<RViewportData>)

#endif
