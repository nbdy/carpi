//
// Created by insane on 11.07.20.
//

#include "MusicPlayer.h"
#include "ui_musicplayer.h"

// todo lst_albums populate; select and only load selected albums
// todo qpushbutton animation
// todo icons instead of words > no i18n needed

MusicPlayer::MusicPlayer(QWidget *parent): QWidget(parent), ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    playerLayout = new QGridLayout(this);
    player = new Player(this);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 150px;}");
    playerLayout->addWidget(player);
    ui->tab_player->setLayout(playerLayout);
}

MusicPlayer::~MusicPlayer()
{
    delete player;
    delete playerLayout;
    delete ui;
}

extern "C" MUSICPLAYER_EXPORT QWidget* create() {
    return new MusicPlayer();
}

extern "C" MUSICPLAYER_EXPORT char* getName() {
    return (char*) "MusicPlayer";
}

extern "C" MUSICPLAYER_EXPORT int getDefaultIndex(){
    return 1;
}