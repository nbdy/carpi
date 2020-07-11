//
// Created by insane on 14.06.20.
//

#ifndef CARPI_VIEWSETTINGSAUDIOAUX_H
#define CARPI_VIEWSETTINGSAUDIOAUX_H


#include "../../../WithBack/ViewWithBack.h"

class ViewSettingsAudioAux : public ViewWithBack {
public:
    ViewSettingsAudioAux();
    void show(Manager* mgr) override;
    void setValuesFalse() override;
};


#endif //CARPI_VIEWSETTINGSAUDIOAUX_H
