//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSMAPCACHE_H
#define CARPI_VIEWSETTINGSMAPCACHE_H

#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsMapCache : public ViewWithBack {
private:
    bool clearCacheDirectorySelected = false;
    bool setCacheDirectorySelected = false;
    std::string cacheDirectory;

public:
    ViewSettingsMapCache(KeyboardLayout *keyboard);
    void drawCacheDirectoryTextBox(Manager *mgr);
    void drawDeleteCacheDirectoryButton(Manager* mgr);
    void show(Manager *mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSMAPCACHE_H
