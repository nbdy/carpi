//
// Created by insane on 14.06.20.
//

#include "ViewSettingsMapCache.h"

ViewSettingsMapCache::ViewSettingsMapCache(KeyboardLayout *keyboard) {
    setName("settings map cache");
    setParent("settings map");
}

void ViewSettingsMapCache::drawCacheDirectoryTextBox(Manager *mgr) {
    if(cacheDirectory.empty()) {
        cacheDirectory = mgr->getConfiguration()->getNavigationConfiguration().cacheDirectory;
        setKeyboardBuffer(cacheDirectory);
    }
    if (GuiTextBox((Rectangle){8, 8, 600, 42}, (char*) getKeyboardBuffer().c_str(), mgr->getConfiguration()->getStyleConfiguration().textSize, showKeyboard)) showKeyboard = true;
    processKeyboard();
    setCacheDirectorySelected = GuiButton((Rectangle){654, 8, 84, 42}, "set");
    if(setCacheDirectorySelected) mgr->getConfiguration()->setCacheDirectory(cacheDirectory);
}

void ViewSettingsMapCache::drawDeleteCacheDirectoryButton(Manager *mgr) {
    if(GuiButton((Rectangle){8, 64, 84, 42}, "clear")) clearCacheDirectorySelected = true;
    if(clearCacheDirectorySelected){
        GuiLabel(Rectangle{142, 64, 84, 42}, "clearing cache..");
        std::string clearCacheCommand = "rm -rf " + mgr->getConfiguration()->getNavigationConfiguration().cacheDirectory;
        system(clearCacheCommand.c_str());
        GuiLabel(Rectangle{142, 128, 84, 42}, "recreating cache directory..");
        std::string createCacheDirectoryCommand = "mkdir " + mgr->getConfiguration()->getNavigationConfiguration().cacheDirectory;
        system(createCacheDirectoryCommand.c_str());
        GuiLabel(Rectangle{142, 194, 84, 42}, "done.");
    }
}

void ViewSettingsMapCache::show(Manager *mgr) {
    drawBackButton();
    drawCacheDirectoryTextBox(mgr);
    drawDeleteCacheDirectoryButton(mgr);
}

void ViewSettingsMapCache::setValuesFalse() {
    viewBackSelected = false;
    setCacheDirectorySelected = false;
}
