//
// Created by nbdy on 11.06.20.
//

#include "WidgetManager.h"

void WidgetManager::show(Manager *mgr) {
    widgetMtx.lock();
    for(Widget *w : widgets) w->show(mgr);
    widgetMtx.unlock();
}

void WidgetManager::addWidget(Widget *widget) {
    widgetMtx.lock();
    widgets.emplace_back(widget);
    widgetMtx.unlock();
}

WidgetManager::WidgetManager() {

}
