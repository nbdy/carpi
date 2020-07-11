//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSMAP_H
#define CARPI_VIEWSETTINGSMAP_H

#include "../../WithBack/ViewWithBack.h"

class ViewSettingsMap : public ViewWithBack {
private:
    bool viewSettingsMapDownloadSelected = false;
    bool viewCacheSettingsSelected = false;

public:
    ViewSettingsMap();
    void show(Manager* mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSMAP_H
