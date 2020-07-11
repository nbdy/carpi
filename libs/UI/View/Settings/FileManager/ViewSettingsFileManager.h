//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSFILEMANAGER_H
#define CARPI_VIEWSETTINGSFILEMANAGER_H


#include "../../WithBack/ViewWithBack.h"

class ViewSettingsFileManager : public ViewWithBack {
public:
    ViewSettingsFileManager();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSFILEMANAGER_H
