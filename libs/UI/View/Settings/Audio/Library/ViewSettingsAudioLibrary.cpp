//
// Created by insane on 14.06.20.
//

#include "ViewSettingsAudioLibrary.h"

ViewSettingsAudioLibrary::ViewSettingsAudioLibrary(KeyboardLayout *keyboard) {
    setName("settings audio library");
    setParent("settings audio");
    setKeyboard(keyboard);
}

void ViewSettingsAudioLibrary::show(Manager *mgr) {
    drawBackButton();
    if(setMusicLibraryPathPressed) mgr->getConfiguration()->setMusicLibraryPath(getKeyboardBuffer());
    GuiLabel((Rectangle) {8, 8, 42, 100}, "path:");
    if(currentMusicLibraryPath.empty()) {
        currentMusicLibraryPath = mgr->getConfiguration()->getMusicConfiguration().path;
        setKeyboardBuffer(currentMusicLibraryPath);
    } else {
        setKeyboardBuffer(getKeyboardBuffer());
    }
    setMusicLibraryPathPressed = GuiButton((Rectangle) {654, 8, 42, 50}, "set");
    drawBackButton();
    if(GuiTextBox((Rectangle) {8, 8, 642, 35}, (char*) currentMusicLibraryPath.c_str() , mgr->getConfiguration()->getStyleConfiguration().textSize, false)) showKeyboard = true;
    if(viewBackSelected) showKeyboard = false;
    processKeyboard();
}

void ViewSettingsAudioLibrary::setValuesFalse() {
    viewBackSelected = false;
    setMusicLibraryPathPressed = false;
}
