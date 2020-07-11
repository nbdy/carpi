//
// Created by insane on 14.06.20.
//

#include "ViewUpdater.h"

ViewUpdater::ViewUpdater() {
    setName("updater");
    setParent("main menu");
}

void ViewUpdater::drawUrlTextbox(Manager *mgr) {
    GuiLabel((Rectangle){8, 8, 420, 42}, mgr->getConfiguration()->getUpdaterConfiguration().url.c_str());
}

void ViewUpdater::drawUpdateButton() {
    updateButtonSelected = GuiButton((Rectangle) {8, 50, 200, 100}, "update");
}

void ViewUpdater::drawUpdatingInformation() {
    if(isUpdating) {
        GuiProgressBar((Rectangle) {8, 154, 420, 42}, nullptr, nullptr, updateProgress, 0, 1);
        if(GuiListView((Rectangle){8, 200, 420, 300}, Utils::joinList(u->getOutput(), ";").c_str(), &listViewScrollIndex, listViewActive)) listViewEditMode = !listViewEditMode;
    }

    if(updateFailed) GuiLabel((Rectangle) {8, 154, 142, 42}, "cant update; most likely no internet");
}

void ViewUpdater::show(Manager *mgr) {
    if(u != nullptr) updateProgress = u->getProgress();

    drawBackButton();
    drawSettingsButton();
    drawUrlTextbox(mgr);
    drawUpdateButton();
    drawUpdatingInformation();

    if(updateButtonSelected && !isUpdating){
        if(mgr->getNetwork()->getIPAddress().empty()) updateFailed = true;
        else {
            isUpdating = true;
            u = new Updater(mgr->getConfiguration()->getUpdaterConfiguration());
            ut = u->getThread();
            ut.detach();
        }
    }
}

void ViewUpdater::setValuesFalse() {
    viewBackSelected = false;
}
