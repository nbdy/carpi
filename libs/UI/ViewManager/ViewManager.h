//
// Created by nbdy on 11.06.20.
//

#ifndef CARPI_VIEWMANAGER_H
#define CARPI_VIEWMANAGER_H

#include <vector>
#include <string>
#include "../View/View.h"
#include "../WidgetManager/WidgetManager.h"
#include "../ToastManager/ToastManager.h"
#include "../Sidebar/Sidebar.h"
#include "../Keyboard/Layout/KeyboardLayout.h"

class ViewManager {
private:
    std::vector<View*> views;
    std::string currentView;
    KeyboardLayout* keyboard;
    WidgetManager *widgetManager;
    ToastManager *toastManager;
    Sidebar *sidebar;

public:
    explicit ViewManager(Manager* mgr);
    void buildUI();
    View* getCurrentView();
    void setValuesFalse();
    void loop(Manager *mgr);
};


#endif //CARPI_VIEWMANAGER_H
