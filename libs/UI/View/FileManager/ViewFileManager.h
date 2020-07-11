//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWFILEMANAGER_H
#define CARPI_VIEWFILEMANAGER_H


#include "../WithBackAndSettings/ViewWithBackAndSettings.h"

class ViewFileManager : public ViewWithBackAndSettings {
private:
    std::vector<std::string> currentDirectoryFileList = {};
    std::string currentDirectory;

    int currentPathTextViewSelected = 0;
    bool currentDirectoryFileListSelected = false;
    int currentDirectoryFileListIndex = 0;
    bool currentDirectoryFileListEditMode = false;

public:
    ViewFileManager(); // todo file edit widget; directory navigation; .. to navigate up
    void drawFileList();
    void drawCurrentPathTextView(Manager* mgr);
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWFILEMANAGER_H
