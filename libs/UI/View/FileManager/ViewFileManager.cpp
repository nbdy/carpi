//
// Created by insane on 14.06.20.
//

#include "ViewFileManager.h"

ViewFileManager::ViewFileManager() {
    setName("file manager");
    setParent("main menu");
    currentDirectory = "/home/" + Utils::getUsername() + "/";
    currentDirectoryFileList = Utils::listDirectory(currentDirectory, false);
}

void ViewFileManager::drawFileList() {
    currentDirectoryFileList = Utils::listDirectory(currentDirectory, false);
    currentPathTextViewSelected = GuiListView((Rectangle){8, 54, 342, 420}, Utils::joinList(currentDirectoryFileList, ";").c_str(), &currentDirectoryFileListIndex, currentPathTextViewSelected);
    // currentDirectory = getCurrentlySelectedFile(); // todo fix
}

void ViewFileManager::drawCurrentPathTextView(Manager *mgr) {
    currentPathTextViewSelected = GuiTextBox((Rectangle){8, 8, 420, 42}, (char*) currentDirectory.c_str(), mgr->getConfiguration()->getStyleConfiguration().textSize, currentDirectoryFileListSelected);
}

void ViewFileManager::show(Manager *mgr) {
    drawBackButton();
    drawSettingsButton();
    drawCurrentPathTextView(mgr);
    drawFileList();
}

void ViewFileManager::setValuesFalse() {
    viewBackSelected = false;
    viewSettingsSelected = false;
}
