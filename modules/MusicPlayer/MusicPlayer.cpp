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
    libraryLayout = new QGridLayout(this);
    player = new Player(this);
    library = new Library(player);
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 150px;}");
    playerLayout->addWidget(player);
    libraryLayout->addWidget(library);
    ui->tab_player->setLayout(playerLayout);
    ui->tab_library->setLayout(libraryLayout);
}

MusicPlayer::~MusicPlayer()
{
    delete library;
    delete libraryLayout;
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

extern "C" MUSICPLAYER_EXPORT QStringList getSettingsKeys(){
    return QStringList() << KEY_SETTINGS_VOLUME << KEY_SETTINGS_DEFAULT_ALBUM << KEY_SETTINGS_DIRECTORY
                         << KEY_SETTINGS_MUTE << KEY_SETTINGS_PLAY_ALBUM_ON_START << KEY_SETTINGS_SHUFFLE;
}