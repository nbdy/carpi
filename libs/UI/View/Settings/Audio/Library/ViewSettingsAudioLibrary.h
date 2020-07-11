//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSAUDIOLIBRARY_H
#define CARPI_VIEWSETTINGSAUDIOLIBRARY_H


#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsAudioLibrary : public ViewWithBack {
private:
    bool setMusicLibraryPathPressed = false;
    std::string currentMusicLibraryPath;
public:
    ViewSettingsAudioLibrary(KeyboardLayout* keyboard);
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSAUDIOLIBRARY_H
