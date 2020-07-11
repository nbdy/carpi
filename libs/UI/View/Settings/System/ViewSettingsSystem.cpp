//
// Created by insane on 14.06.20.
//

#include "ViewSettingsSystem.h"

ViewSettingsSystem::ViewSettingsSystem() {
    setName("settings system");
    setParent("settings");
}

void ViewSettingsSystem::drawShutoffButton() {
    if(GuiButton((Rectangle) {8, 8, 200, 100}, "shutoff")) shutoffSelected = true;
    if(shutoffSelected) { // reassure
        DrawRectangle(100, 100, 600, 300, GREEN);
        DrawRectangle(104, 104, 592, 292, BLACK);
        DrawText("shutdown?", 242, 142, 20, GREEN);
        if(GuiButton((Rectangle){142, 242, 200, 100}, "yes")) system("sudo shutdown now");
        if(GuiButton((Rectangle){420, 242, 200, 100}, "no")) shutoffSelected = false;
    }
}

void ViewSettingsSystem::drawRebootButton() {
    if(GuiButton((Rectangle){8, 128, 200, 100}, "reboot")) rebootSelected = true;
    if(rebootSelected){
        DrawRectangle(100, 100, 600, 300, GREEN);
        DrawRectangle(104, 104, 592, 292, BLACK);
        DrawText("reboot?", 242, 142, 20, GREEN);
        if(GuiButton((Rectangle){142, 242, 200, 100}, "yes")) system("sudo reboot");
        if(GuiButton((Rectangle){420, 242, 200, 100}, "no")) rebootSelected = false;
    }
}

void ViewSettingsSystem::drawRestartButton() {
    if(GuiButton((Rectangle){224, 8, 200, 100}, "restart")) restartSelected = true;
    if(restartSelected){
        DrawRectangle(100, 100, 600, 300, GREEN);
        DrawRectangle(104, 104, 592, 292, BLACK);
        DrawText("restart this program?", 242, 142, 20, GREEN);
        if(GuiButton((Rectangle){142, 242, 200, 100}, "yes")) system("sudo killall carpi ; sudo carpi");
        if(GuiButton((Rectangle){420, 242, 200, 100}, "no")) restartSelected = false;
    }
}

void ViewSettingsSystem::show(Manager *mgr) {
    drawShutoffButton();
    drawRebootButton();
    drawRestartButton();
    drawBackButton();
}

void ViewSettingsSystem::setValuesFalse() {
    viewBackSelected = false;
}
