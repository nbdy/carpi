//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSUPDATER_H
#define CARPI_VIEWSETTINGSUPDATER_H


#include "../../WithBack/ViewWithBack.h"

class ViewSettingsUpdater : public ViewWithBack {
private:
    bool setProjectUrlSelected = false;
    bool onBootCheckboxChecked = false;
    std::string projectUrl;

public:
    explicit ViewSettingsUpdater(KeyboardLayout* keyboard);
    void drawUrlTextbox(Manager* mgr);
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSUPDATER_H
