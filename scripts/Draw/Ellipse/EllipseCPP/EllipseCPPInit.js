function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseCPP", "&Full Ellipse"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseCPP.js");
    action.setIcon(basePath + "/EllipseCPP.svg");
    action.setStatusTip(qsTranslate("EllipseCPP", "Draw full ellipse from center, major point and ratio"));
    action.setDefaultShortcut(new QKeySequence("e,p"));
    action.setDefaultCommands(["ellipse", "ep"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Ellipse, true, true, true);
}
