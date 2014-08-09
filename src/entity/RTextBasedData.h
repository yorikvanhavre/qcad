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

#ifndef RTEXTBASEDDATA_H
#define RTEXTBASEDDATA_H

#include "entity_global.h"

#include <QTextLayout>

#include "RDocument.h"
#include "REntityData.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RVector.h"

class QTextDocument;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a text based entity (text, block attribute, block attribute definition).
 *
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RTextBasedData: public REntityData, public RPainterPathSource {
    friend class RTextBasedEntity;

protected:
    RTextBasedData(RDocument* document, const RTextBasedData& data);

public:
    RTextBasedData(RDocument* document = NULL);
    RTextBasedData(const RVector& position,
              const RVector& alignmentPoint,
              double textHeight,
              double textWidth,
              RS::VAlign verticalAlignment,
              RS::HAlign horizontalAlignment,
              RS::TextDrawingDirection drawingDirection,
              RS::TextLineSpacingStyle lineSpacingStyle,
              double lineSpacingFactor,
              const QString& text,
              const QString& fontName,
              bool bold,
              bool italic,
              double angle,
              bool simple);
    virtual ~RTextBasedData() {}

    bool isValid() const {
        return !text.isNull();
    }

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;
    double getWidth() const;
    double getHeight() const;

    void sync(const RTextBasedData& other);

    virtual RVector getPointOnEntity() const;

    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox);
        return QList<RVector>();
    }
    virtual QList<RVector> getMiddlePoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox);
        return QList<RVector>();
    }
    virtual QList<RVector> getCenterPoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox);
        return QList<RVector>();
    }
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny, const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(distance);
        Q_UNUSED(from);
        Q_UNUSED(queryBox);

        return QList<RVector>();
    }

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false) const;
    virtual bool intersectsWith(const RShape& shape) const;

    RVector getPosition() const {
        return position;
    }

    void setPosition(const RVector& position) {
        this->position = position;
    }

    RVector getAlignmentPoint() const {
        return alignmentPoint;
    }

    void setAlignmentPoint(const RVector& alignmentPoint) {
        this->alignmentPoint = alignmentPoint;
    }

    void setText(const QString& text);

    QString getFontName() const {
        return fontName;
    }

    void setFontName(const QString& fontName) {
        this->fontName = fontName;
        update();
    }

    bool isBold() const {
        return bold;
    }

    void setBold(bool on) {
        bold = on;
        update();
    }

    bool isItalic() const {
        return italic;
    }

    void setItalic(bool on) {
        italic = on;
        update();
    }

    double getTextHeight() const {
        return textHeight;
    }

    void setTextHeight(double h) {
        this->textHeight = h;
        update();
    }

    /**
     * Width of the text box used for line wrapping (not supported).
     */
    double getTextWidth() const {
        return textWidth;
    }

    void setTextWidth(double w) {
        this->textWidth = w;
        update();
    }

    void setVAlign(RS::VAlign valign) {
        this->verticalAlignment = valign;
        update();
    }

    RS::VAlign getVAlign() const {
        return this->verticalAlignment;
    }

    void setHAlign(RS::HAlign halign) {
        this->horizontalAlignment = halign;
        update();
    }

    RS::HAlign getHAlign() const {
        return this->horizontalAlignment;
    }

    void setDrawingDirection(RS::TextDrawingDirection drawingDirection) {
        this->drawingDirection = drawingDirection;
        update();
    }

    RS::TextDrawingDirection getDrawingDirection() const {
        return drawingDirection;
    }

    void setLineSpacingStyle(RS::TextLineSpacingStyle lineSpacingStyle) {
        this->lineSpacingStyle = lineSpacingStyle;
        update();
    }

    RS::TextLineSpacingStyle getLineSpacingStyle() const {
        return lineSpacingStyle;
    }

    void setLineSpacingFactor(double lineSpacingFactor) {
        this->lineSpacingFactor = lineSpacingFactor;
        update();
    }

    double getLineSpacingFactor() const {
        return lineSpacingFactor;
    }

    void setAngle(double angle) {
        this->angle = angle;
        update();
    }

    double getAngle() const {
        return angle;
    }

    void setXScale(double xScale) {
        this->xScale = xScale;
        update();
    }

    double getXScale() const {
        return xScale;
    }

    void setSimple(bool on) {
        simple = on;
        update();
    }

    bool isSimple() const {
        return simple;
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();

    virtual QString getText() const {
        return text;
    }
    virtual QString getRenderedText(bool escapeUnicode = false) const;
    virtual QString getPlainText() const;
    virtual QString getEscapedText(bool escapeUnicode = false) const;
    static QString escapeUnicode(const QString& str);
    virtual QFont getMainFont() const;

    virtual void update() const;
    virtual bool isDirty() const;

    virtual QList<RPainterPath> getPainterPaths(bool draft = false) const;
    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const;
    virtual QList<QSharedPointer<RShape> > getExploded() const;

    virtual QSharedPointer<RShape> getClosestShape(const RVector& pos, double range = RNANDOUBLE) const {
        Q_UNUSED(pos);
        Q_UNUSED(range);
        return QSharedPointer<RShape>();
    }

    virtual RVector getClosestPointOnEntity(const RVector& point, double range, bool limited) const;

//    virtual RTextBasedData getRenderedTextData() const {
//        return *this;
//    }

    static QString toEscapedText(const QTextDocument& textDocument, const RColor& initialColor, double fontHeightFactor=1.0);
    static QString toRichText(const QString& escapedText, const QFont& mainFont, double fontHeightFactor=1.0);

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, const RTextBasedData& t);

protected:
    QString text;
    RVector position;
    RVector alignmentPoint;
    double textHeight;
    double textWidth;
    RS::VAlign verticalAlignment;
    RS::HAlign horizontalAlignment;
    RS::TextDrawingDirection drawingDirection;
    RS::TextLineSpacingStyle lineSpacingStyle;
    double lineSpacingFactor;
    QString fontName;
    bool bold;
    bool italic;
    double angle;
    double xScale;
    bool simple;

    mutable double height;
    mutable double width;
    mutable RBox boundingBox;
    mutable QList<RPainterPath> painterPaths;
    mutable bool dirty;
    mutable bool gotDraft;
};

Q_DECLARE_METATYPE(RTextBasedData)
Q_DECLARE_METATYPE(RTextBasedData*)
Q_DECLARE_METATYPE(const RTextBasedData*)
Q_DECLARE_METATYPE(QSharedPointer<RTextBasedData>)
Q_DECLARE_METATYPE(QSharedPointer<RTextBasedData>*)

#endif
