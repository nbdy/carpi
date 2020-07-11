//
// Created by insane on 14.06.20.
//

#include "ViewSettingsMapDownload.h"

ViewSettingsMapDownload::ViewSettingsMapDownload() {
    setName("settings map download");
    setParent("settings map");
}

void ViewSettingsMapDownload::show(Manager *mgr) {
    drawBackButton();
    if(!downloadItemsInitialized){
        auto ncfg = mgr->getConfiguration()->getNavigationConfiguration();
        for(auto& e : ncfg.mapDownloads.items()) {
            keys.emplace_back(e.key());
            values.emplace_back(e.value());
        }
        downloadItems = Utils::joinList(keys, ";");
        downloadItemsInitialized = true;
    }

    if(downloadListViewItemSelected >= 0){
        downloadItemSelected = GuiButton((Rectangle){8, 442, 200, 100}, "download");
        GuiLabel(Rectangle{142, 8, 142, 42}, keys[downloadListViewItemSelected].c_str());
        GuiLabel(Rectangle{142, 42, 142, 42}, values[downloadListViewItemSelected].c_str());
        // todo show approx size
        if(downloadItemSelected) {
            // todo show progressbar and do download if internet connection is existent
        }
    }
    if(GuiListView((Rectangle){8, 8, 128, 420}, downloadItems.c_str(), &downloadListViewScrollIndex, downloadListViewItemSelected))
        downloadListEditMode = !downloadListEditMode;
}

void ViewSettingsMapDownload::setValuesFalse() {
    viewBackSelected = false;
    downloadListViewSelected = false;
    downloadItemSelected = false;
}

bool ViewSettingsMapDownload::getDownloadListViewSelected() {
    return downloadListViewSelected;
}
