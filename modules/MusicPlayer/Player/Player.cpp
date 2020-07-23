//
// Created by insane on 23.07.20.
//

#include "Player.h"
#include "ui_player.h"

Player::Player(QWidget *parent):  QWidget(parent), ui(new Ui::Player){
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);

    ui->lbl_artist->setText("None");
    ui->lbl_album->setText("None");
    ui->lbl_song->setText("None");

    connect(ui->btn_playPause, SIGNAL(clicked()), this, SLOT(playPauseClicked()));
    connect(ui->btn_next, SIGNAL(clicked()), playlist, SLOT(next()));
    connect(ui->btn_previous, SIGNAL(clicked()), playlist, SLOT(previous()));

    connect(ui->cb_shuffle, SIGNAL(stateChanged(int)), this, SLOT(shuffleCheckedChanged()));
    connect(ui->cb_mute, SIGNAL(stateChanged(int)), this, SLOT(muteCheckedChanged()));
    connect(ui->cb_play_on_start, SIGNAL(stateChanged(int)), this, SLOT(playOnStartCheckedChanged()));

    connect(ui->sldr_song, SIGNAL(valueChanged(int)), this, SLOT(onSongPositionSliderChanged(int)));
    connect(ui->sldr_volume, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueSliderChanged(int)));

    connect(player, SIGNAL(mediaChanged(const QMediaContent&)), this, SLOT(onNextSong()));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64))); // ^

    settings = ISettings::getSettings(this);
    createDefaultSettings();
    loadSettings();
}

Player::~Player() {
    settings->sync();
    delete settings;
    delete player;
    delete ui;
}

void Player::createDefaultSettings() {
    if(!settings->contains(getName())) return;
    Logger::info(getName(), "setting default settings");
    settings->beginGroup(getName());
    settings->setValue(KEY_SETTINGS_DIRECTORY, "~/Music/");
    settings->setValue(KEY_SETTINGS_VOLUME, 30);
    settings->setValue(KEY_SETTINGS_SHUFFLE, false);
    settings->setValue(KEY_SETTINGS_PLAY_ALBUM_ON_START, false); // todo actually use this
    settings->setValue(KEY_SETTINGS_PLAY_ON_START, false);
    settings->setValue(KEY_SETTINGS_DEFAULT_ALBUM, "");
    settings->endGroup();
}

void Player::loadSettings() {
    Logger::info(getName(), "loading settings");
    settings->beginGroup(getName());

    bool muted = settings->value(KEY_SETTINGS_MUTE).toBool();
    player->setMuted(muted);
    ui->cb_mute->setChecked(muted);

    ui->cb_shuffle->setChecked(settings->value(KEY_SETTINGS_SHUFFLE).toBool());

    int volume = settings->value(KEY_SETTINGS_VOLUME).toInt();
    ui->sldr_volume->setValue(volume);
    player->setVolume(volume);

    QString defaultAlbum = settings->value(KEY_SETTINGS_DEFAULT_ALBUM).toString();
    if(defaultAlbum != "") loadAlbum(defaultAlbum);

    settings->endGroup();
}

void Player::loadAlbum(const QString& path) {
    if(!playlist->clear()) Logger::warning(getName(), "could not clear playlist"); // todo inform ui
    QDir albumDirectory(path);
    setValue(KEY_SETTINGS_DEFAULT_ALBUM, path);
    Logger::info(getName(), "populating playlist from '" + albumDirectory.absolutePath() + "'");
    for(const QString& fp : albumDirectory.entryList(QStringList() << "*.mp3" << "*.wav", QDir::Files)) {
        QString afp = albumDirectory.absoluteFilePath(fp);
        Logger::debug(getName(), "adding '" + afp + "' to current playlist");
        playlist->addMedia(QUrl::fromLocalFile(afp));
    }
}

void Player::playPauseClicked() {
    if(playing) player->pause();
    else player->play();
}

void Player::shuffleCheckedChanged() {
    setValue(KEY_SETTINGS_SHUFFLE, ui->cb_shuffle->isChecked()); // todo actually shuffle when enabled
}

void Player::muteCheckedChanged() {
    bool muted = ui->cb_mute->isChecked();
    setValue(KEY_SETTINGS_MUTE, muted);
    player->setMuted(muted);
}

void Player::onNextSong() {
    // todo implement shuffle here
    ui->lbl_artist->setText(player->metaData(QMediaMetaData::AlbumArtist).toString());
    ui->lbl_album->setText(player->metaData(QMediaMetaData::AlbumTitle).toString());
    ui->lbl_song->setText(player->metaData(QMediaMetaData::Title).toString());
    // todo use player->metaData(QMediaMetaData::CoverArtImage);
}

void Player::playOnStartCheckedChanged() {
    setValue(KEY_SETTINGS_PLAY_ON_START, ui->cb_play_on_start->isChecked());
}

void Player::onSongPositionSliderChanged(int pos) {
    player->setPosition(pos);
}

void Player::onVolumeValueSliderChanged(int pos) {
    setValue(KEY_SETTINGS_VOLUME, pos);
    player->setVolume(pos);
}

void Player::onDurationChanged(qint64 duration) {
    ui->lbl_max_position->setText(QString::number(duration)); // todo convert to mm:ss
}

void Player::onPositionChanged(qint64 position) {
    ui->lbl_current_position->setText(QString::number(position)); // todo convert to mm:ss
}

QString Player::getName() {
    return "MusicPlayer";
}

template<typename T>
void Player::setValue(const QString &key, T value) {
    settings->beginGroup(getName());
    settings->setValue(key, value);
    settings->endGroup();
}
