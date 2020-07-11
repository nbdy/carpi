//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSUI_H
#define CARPI_VIEWSETTINGSUI_H

#include "../../WithBack/ViewWithBack.h"

class ViewSettingsUI : public ViewWithBack {
public:
    ViewSettingsUI();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSUI_H
