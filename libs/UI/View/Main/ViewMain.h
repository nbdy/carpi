//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWMAIN_H
#define CARPI_VIEWMAIN_H


#include "../View.h"
#include "../../../../raygauge/libs/Circle/Circle.h"

class ViewMain : public View {
private:
    bool mainMenuSelected = false;
    raygauge::Circle *speedGauge;

public:
    ViewMain();
    void _initSpeedGauge();
    void drawDashboardGPSValues(Position* position);
    void drawDashboardStatic();
    void drawDashboardNetworkValues(Network* network); // todo fix rpi display same ip both interfaces
    void drawDashboardSystemValues(Manager* mgr);
    void drawSpeedGauge(Manager *mgr);
    void show(Manager* mgr) override;
    std::string getNextView() override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWMAIN_H
