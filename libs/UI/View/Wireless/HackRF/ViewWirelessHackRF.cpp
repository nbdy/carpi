//
// Created by insane on 14.06.20.
//

#include "ViewWirelessHackRF.h"

ViewWirelessHackRF::ViewWirelessHackRF() {
    setName("wireless hackrf");
    setParent("wireless");
}

void ViewWirelessHackRF::drawSweepUi() {
    if(!GuiButton(Rectangle{8, 8, 142, 42}, "sweep")) return;
}

void ViewWirelessHackRF::show(Manager *mgr) {
    drawBackButton();
    drawSettingsButton();
    drawSweepUi();
}

void ViewWirelessHackRF::setValuesFalse() {
    viewSweepUiButtonClicked = false;
    viewBackSelected = false;
    viewSettingsSelected = false;
}
