//
// Created by insane on 11.07.20.
//

#include "MusicPlayer.h"
#include "ui_musicplayer.h"


MusicPlayer::MusicPlayer(QWidget *parent): QMainWindow(parent), ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    createDefaultSettings();
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::createDefaultSettings() {
    QSettings *s = ISettings::getSettings(this);
    s->beginGroup(getName());
    s->setValue(KEY_SETTINGS_DIRECTORY, "~/Music/");
    s->setValue(KEY_SETTINGS_VOLUME, 50);
    s->setValue(KEY_SETTINGS_SHUFFLE, false);
    s->endGroup();
}

extern "C" MUSICPLAYER_EXPORT QWidget* create() {
    return new MusicPlayer();
}

extern "C" MUSICPLAYER_EXPORT char* getName() {
    return (char*) "MusicPlayer";
}

extern "C" MUSICPLAYER_EXPORT int getDefaultIndex(){
    return 2;
}