//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_WIDGETMANAGER_H
#define CARPI_WIDGETMANAGER_H

#include <mutex>
#include <vector>
#include "../../Manager/Manager.h"
#include "../Widget/Widget.h"

class WidgetManager {
private:
    std::mutex widgetMtx;
    std::vector<Widget*> widgets;

public:
    WidgetManager();
    void show(Manager* mgr);
    void addWidget(Widget* widget);
};


#endif //CARPI_WIDGETMANAGER_H
