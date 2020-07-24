//
// Created by insane on 23.07.20.
//

#include "Library.h"
#include "ui_library.h"


Library::Library(Player *player, QWidget *parent): QWidget(parent), ui(new Ui::Library) {
    ui->setupUi(this);
    this->player = player;
    selectedAlbums = new QList<AlbumItem*>();
    populateAlbums();
    connect(ui->lst_albums, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onAlbumSelected(QListWidgetItem*)));
    connect(ui->lst_songs, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSongSelected(QListWidgetItem*)));
}

Library::~Library() {
    delete ui;
}

void Library::populateSongs() {
    ui->lst_songs->clear();
    QDir musicDir(player->getMusicDirectory());
    Logger::info(getName(), "populating song list");
    for(auto *item : selectedAlbums->toVector()){
        QDir albumDir(musicDir.absoluteFilePath(item->getPath()));
        Logger::debug(getName(), "from album: " + albumDir.absolutePath());
        for(const QString& s : albumDir.entryList(QStringList() << "*.mp3")) { // todo maybe more file types
            Logger::debug(getName(), "found song: " + s);
            ui->lst_songs->addItem(new SongItem(albumDir.absoluteFilePath(s)));
        }
    }
}

void Library::populateAlbums() {
    ui->lst_albums->clear();
    QDir musicLib(player->getMusicDirectory());
    Logger::info(getName(), "populating album list from: " + musicLib.absolutePath());
    for(const QString& a : musicLib.entryList(QDir::Dirs)) {
        Logger::debug(getName(), "found: " + a);
        // todo ignore . .. etc
        ui->lst_albums->addItem(new AlbumItem(musicLib.absoluteFilePath(a)));
    }
}

QString Library::getName() {
    return "MusicPlayer::Library";
}

void Library::onSongSelected(QListWidgetItem *item) {
    auto *si = dynamic_cast<SongItem*>(item);
    Logger::debug(getName(), "going to play: " + si->getPath());
    auto *mp = player->getMediaPlayer();
    auto *p = new QMediaPlaylist();
    emit mp->stop();
    p->clear();
    p->addMedia(QUrl::fromLocalFile(si->getPath()));
    for(QListWidgetItem *i : ui->lst_songs->findItems("*", Qt::MatchWildcard)){
        si = dynamic_cast<SongItem*>(i);
        p->addMedia(QUrl::fromLocalFile(si->getPath()));
    }
    mp->setPlaylist(p);
    emit mp->play();
}

void Library::onAlbumSelected(QListWidgetItem *item) {
    auto *ai = dynamic_cast<AlbumItem*>(item);
    if(!ui->cb_select_multiple->isChecked()) selectedAlbums->clear();
    selectedAlbums->append(ai);
    populateSongs();
}
