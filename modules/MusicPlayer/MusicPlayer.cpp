//
// Created by insane on 11.07.20.
//

#include "MusicPlayer.h"
#include "ui_musicplayer.h"


MusicPlayer::MusicPlayer(QWidget *parent): QMainWindow(parent), ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    // todo signals and slots for labels
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
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