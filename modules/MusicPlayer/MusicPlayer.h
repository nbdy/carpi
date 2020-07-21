//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MUSICPLAYER_H
#define CARPI_QT_MUSICPLAYER_H

#define KEY_SETTINGS_DIRECTORY "directory"
#define KEY_SETTINGS_VOLUME "volume"
#define KEY_SETTINGS_SHUFFLE "shuffle"

#include "MusicPlayer_global.h"
#include "../../libs/ISettings/ISettings.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MusicPlayer; }
QT_END_NAMESPACE

class MusicPlayer : public QMainWindow
{
Q_OBJECT
private:
    Ui::MusicPlayer *ui;

    void createDefaultSettings();

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer() override;
};

extern "C" {
    MUSICPLAYER_EXPORT int getDefaultIndex();
    MUSICPLAYER_EXPORT char* getName();
    MUSICPLAYER_EXPORT QWidget* create();
};


#endif //CARPI_QT_MUSICPLAYER_H
