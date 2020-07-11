//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSSYSTEM_H
#define CARPI_VIEWSETTINGSSYSTEM_H


#include "../../WithBack/ViewWithBack.h"

class ViewSettingsSystem : public ViewWithBack {
private:
    bool shutoffSelected = false;
    bool rebootSelected = false;
    bool restartSelected = false;

public:
    ViewSettingsSystem();
    void drawShutoffButton();
    void drawRebootButton();
    void drawRestartButton();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSSYSTEM_H
