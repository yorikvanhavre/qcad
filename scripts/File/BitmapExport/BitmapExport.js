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

include("../File.js");
include("BitmapExportWorker.js");

function BitmapExport(guiAction) {
    File.call(this, guiAction);
}

BitmapExport.prototype = new File();

BitmapExport.includeBasePath = includeBasePath;

BitmapExport.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);

    var bmpFileName = this.getFilename();

    if (isNull(bmpFileName)) {
        this.terminate();
        return;
    }

    var properties = this.getProperties();
    if (isNull(properties)) {
        this.terminate();
        return;
    }

    var res = this.exportBitmap(this.getDocumentInterface(), bmpFileName, properties);

    var appWin = EAction.getMainWindow();
    if (!res[0]) {
        print("Error: cannot save file: ", fileName);
        print("Error: ", res[1]);
        appWin.handleUserWarning(
                qsTr("Error while generating Bitmap file '%1': %2")
                    .arg(bmpFileName).arg(res[1]));
        appWin.handleUserWarning();
    }
    else {
        appWin.handleUserMessage(
                qsTr("Bitmap file has been exported to '%1'").arg(bmpFileName));
    }

    this.terminate();
};

BitmapExport.prototype.getFilename = function() {
    var fi;

    var drawingFileName = this.getDocument().getFileName();
    var initialPath = "";
    //var initialFile = "";
    if (drawingFileName.length === 0) {
        fi = new QFileInfo(QDir.homePath());
        initialPath = fi.absoluteFilePath() + QDir.separator
                + stripDirtyFlag(EAction.getMdiChild().windowTitle);
        //initialFile = fi.completeBaseName();
    } else {
        fi = new QFileInfo(drawingFileName);
        initialPath = fi.path() + QDir.separator + fi.completeBaseName();
    }

    var formats = QImageWriter.supportedImageFormats();
    var filters = [];

    var filterAllImages = "";
    for (var i=0; i<formats.length; ++i) {
        var format = formats[i];
        var formatAlt = "";
        if (format==="jpg" || format==="tif") {
            continue;
        }

        if (format==="jpeg") {
            formatAlt = "jpg";
        }
        else if (format==="tiff") {
            formatAlt = "tif";
        }

        //if (filters.length!==0) {
        //    filters += ";;";
        //}

        var filter = format.toUpper() + " " + qsTr("Files") + " (";
        if (formatAlt.length!==0) {
            filter += "*." + formatAlt + " ";
        }
        filter += "*." + format;
        filter += ")";

        filters.push(filter);
    }

    var ret = File.getSaveFileName(this, qsTr("Export as Bitmap"),
                   initialPath, filters);

    if (isNull(ret)) {
        return undefined;
    }

    var fileName = ret[0];

    if (isNull(fileName) || fileName.length===0) {
        return undefined;
    }

    return fileName;
};

BitmapExport.prototype.getProperties = function() {
    var appWin = EAction.getMainWindow();
    var dialog = WidgetFactory.createDialog(BitmapExport.includeBasePath, "BitmapExportDialog.ui", appWin);

    var widthEdit = dialog.findChild("Width");
    var heightEdit = dialog.findChild("Height");
    var resolutionCombo = dialog.findChild("Resolution");
    var marginCombo = dialog.findChild("Margin");

    var whiteRadio = dialog.findChild("WhiteBackground");
    var blackRadio = dialog.findChild("BlackBackground");

    var document = this.getDocument();
    var documentWidth = document.getBoundingBox(true, true).getWidth();
    var documentHeight = document.getBoundingBox(true, true).getHeight();

    widthEdit.valueChanged.connect(
                function() {
                    resolutionCombo.index = 0;
                });
    heightEdit.valueChanged.connect(
                function() {
                    resolutionCombo.index = 0;
                });
    resolutionCombo.editTextChanged.connect(
                function(str) {
                    if (str==="auto") {
                        return;
                    }

                    var res = parseInt(str, 10);
                    if (isNaN(res)) {
                        return;
                    }

                    widthEdit.setValue(res * documentWidth);
                    heightEdit.setValue(res * documentHeight);
                });

    if (!dialog.exec()) {
        dialog.destroy();
        return undefined;
    }

    var ret = [];

    ret["width"] = widthEdit.getValue();
    ret["height"] = heightEdit.getValue();
    if (whiteRadio.checked) {
        ret["backgroundColor"] = new QColor("white");
    }
    else {
        ret["backgroundColor"] = new QColor("black");
    }
    ret["margin"] = RMath.eval(marginCombo.currentText);

    dialog.destroy();
    return ret;
};

BitmapExport.prototype.exportBitmap = function(di, fileName, properties) {
    // make sure nothing is selected:
    di.deselectAll();
    var view = di.getLastKnownViewWithFocus();
    var scene = view.getScene();

    return exportBitmap(di.getDocument(), scene, fileName, properties);
    //var document = this.getDocument();
    //var di = this.getDocumentInterface();
//    var document = di.getDocument();

//    // make sure nothing is selected:
//    di.deselectAll();

//    var v = di.getLastKnownViewWithFocus();
//    var scene = v.getScene();
//    var view = new RGraphicsViewImage();
//    view.setScene(scene, false);
//    view.setAntialiasing(true);
//    view.setPaintOrigin(false);
//    view.setTextHeightThresholdOverride(0);

//    // disabled: produces very thin lines, invisible for units >= Meter
//    //view.setPrinting(true);

//    view.setBackgroundColor(properties.background);
//    view.resizeImage(properties.width, properties.height);

//    view.autoZoom(properties.margin);

//    di.regenerateScenes();

//    // export file
//    var buffer = view.getBuffer();

//    scene.unregisterView(view);
    
//    var iw = new QImageWriter(fileName);
//    // always empty
//    //qDebug("BitmapExport.js:", "exportBitmap(): format:", iw.format());
//    var ext = new QFileInfo(fileName).suffix().toLowerCase();
//    if (ext === "png") {
//        iw.setQuality(9);
//    } else if (ext === "jpg" || ext === "jpeg") {
//        iw.setQuality(95);
//    } else if (ext === "tif" || ext === "tiff") {
//        iw.setCompression(1);
//    } else if (ext === "bmp") {
//        iw.setCompression(1);
//    }

//    var appWin = EAction.getMainWindow();
//    if (!iw.write(buffer)) {
//        print("Error: cannot save file: ", fileName);
//        print("Error: ", iw.errorString());
//        appWin.handleUserWarning(
//                qsTr("Error while generating Bitmap file '%1': %2")
//                    .arg(fileName).arg(iw.errorString()));
//    } else {
//        print("Conversion finished.");
//        appWin.handleUserMessage(
//                qsTr("Bitmap file has been exported to '%1'").arg(fileName));
//    }
//    iw.destroy();
};

