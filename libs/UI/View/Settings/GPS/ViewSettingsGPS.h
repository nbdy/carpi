//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSGPS_H
#define CARPI_VIEWSETTINGSGPS_H


#include "../../WithBack/ViewWithBack.h"

class ViewSettingsGPS : public ViewWithBack {
public:
    ViewSettingsGPS();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSGPS_H
