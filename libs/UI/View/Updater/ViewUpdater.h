//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWUPDATER_H
#define CARPI_VIEWUPDATER_H


#include "../WithBackAndSettings/ViewWithBackAndSettings.h"
#include "../../../Updater/Updater.h"

class ViewUpdater : public ViewWithBackAndSettings {
private:
    bool updateButtonSelected = false;
    bool isUpdating = false;
    bool updateFailed = false;
    int updateProgress = 0;
    int listViewActive = -1;
    int listViewScrollIndex = 0;
    bool listViewEditMode = false;

    Updater *u = nullptr;
    std::thread ut;

public:
    ViewUpdater();
    void drawUrlTextbox(Manager* mgr);
    void drawUpdateButton();
    void drawUpdatingInformation();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWUPDATER_H
