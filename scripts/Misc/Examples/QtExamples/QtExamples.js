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

include("../Examples.js");

/**
 * \class QtExamples
 * \brief Base class for all Qt examples.
 */
function QtExamples(guiAction) {
    EAction.call(this, guiAction);
}

QtExamples.prototype = new EAction();
QtExamples.includeBasePath = includeBasePath;

QtExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        500,
        QtExamples.getTitle(),
        "qtExamples"
    );
    return menu;
};

QtExamples.getToolBar = function() {
    var tb = EAction.getToolBar(QtExamples.getTitle(), "QtExamples");
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

QtExamples.getTitle = function() {
    return qsTr("&Qt");
};

QtExamples.prototype.getTitle = function() {
    return QtExamples.getTitle();
};
