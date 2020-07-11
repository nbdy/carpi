//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSMAPDOWNLOAD_H
#define CARPI_VIEWSETTINGSMAPDOWNLOAD_H


#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsMapDownload : public ViewWithBack {
protected:
    bool downloadItemSelected = false;
    bool downloadListViewSelected = false;
    int downloadListViewItemSelected = -1;
    int downloadListViewScrollIndex = 0;
    bool downloadListEditMode = false;
    bool downloadItemsInitialized = false;
    std::string downloadItems;
    std::vector<std::string> keys;
    std::vector<std::string> values;

public:
    ViewSettingsMapDownload();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
    bool getDownloadListViewSelected();
};


#endif //CARPI_VIEWSETTINGSMAPDOWNLOAD_H
