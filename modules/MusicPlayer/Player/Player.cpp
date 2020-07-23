//
// Created by insane on 23.07.20.
//

#include "Player.h"
#include "ui_player.h"

Player::Player(QWidget *parent): QWidget(parent), ui(new Ui::Player){
    ui->setupUi(this);

    player = new QMediaPlayer(this);

    ui->lbl_artist->setText("None");
    ui->lbl_album->setText("None");
    ui->lbl_song->setText("None");

    connect(ui->btn_playPause, SIGNAL(clicked()), this, SLOT(playPauseClicked()));
    connect(ui->btn_next, SIGNAL(clicked()), this, SLOT(nextClicked()));
    connect(ui->btn_previous, SIGNAL(clicked()), this, SLOT(previousClicked()));

    connect(ui->cb_shuffle, SIGNAL(stateChanged(int)), this, SLOT(shuffleCheckedChanged()));
    connect(ui->cb_mute, SIGNAL(stateChanged(int)), this, SLOT(muteCheckedChanged()));
    connect(ui->cb_play_on_start, SIGNAL(stateChanged(int)), this, SLOT(playOnStartCheckedChanged()));

    connect(ui->sldr_song, SIGNAL(valueChanged(int)), this, SLOT(onSongPositionSliderChanged(int)));
    connect(ui->sldr_volume, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueSliderChanged(int)));

    connect(player, SIGNAL(mediaChanged(const QMediaContent&)), this, SLOT(onNextSong()));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));

    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleMediaPlayerError()));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(handleMediaPlayerMediaStatusChanged()));
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(handleMediaPlayerStateChanged()));

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
    if(settings->contains(getName())) return;
    Logger::info(getName(), "setting default settings");
    settings->beginGroup(getName());
    settings->setValue(KEY_SETTINGS_DIRECTORY, QDir::home().absoluteFilePath("Music")); // todo do not hard code
    settings->setValue(KEY_SETTINGS_VOLUME, 30);
    settings->setValue(KEY_SETTINGS_SHUFFLE, false);
    settings->setValue(KEY_SETTINGS_PLAY_ALBUM_ON_START, false); // todo actually use this
    settings->setValue(KEY_SETTINGS_PLAY_ON_START, false);
    settings->setValue(KEY_SETTINGS_DEFAULT_ALBUM, "");
    settings->endGroup();
    settings->sync();
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

    settings->endGroup();
}

void Player::playPauseClicked() {
    if(player->state() == QMediaPlayer::PlayingState) player->pause();
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

QMediaPlayer *Player::getMediaPlayer() {
    return player;
}

QString Player::getMusicDirectory() {
    settings->beginGroup(getName());
    QString r = settings->value(KEY_SETTINGS_DIRECTORY).toString();
    settings->endGroup();
    return r;
}

void Player::handleMediaPlayerError() {
    Logger::error(getName(), player->errorString());
}

void Player::handleMediaPlayerMediaStatusChanged() {
    auto s = player->mediaStatus();
    QString r = "";
    switch (s) {
        case QMediaPlayer::UnknownMediaStatus:
            r = "UnknownMediaStatus"; break;
        case QMediaPlayer::NoMedia:
            r = "NoMedia"; break;
        case QMediaPlayer::LoadingMedia:
            r = "LoadingMedia"; break;
        case QMediaPlayer::LoadedMedia:
            r ="LoadedMedia"; break;
        case QMediaPlayer::StalledMedia:
            r ="StalledMedia"; break;
        case QMediaPlayer::BufferingMedia:
            r ="BufferingMedia"; break;
        case QMediaPlayer::BufferedMedia:
            r = "BufferedMedia"; break;
        case QMediaPlayer::EndOfMedia:
            r ="EndOfMedia"; break;
        case QMediaPlayer::InvalidMedia:
            r = "InvalidMedia"; break;
    }
    Logger::debug(getName(), r);
}

void Player::handleMediaPlayerStateChanged() {
    if(player->state() == QMediaPlayer::PausedState) ui->btn_playPause->setText(">");
    else ui->btn_playPause->setText("||");
}

void Player::nextClicked() {
    player->playlist()->next();
}

void Player::previousClicked() {
    player->playlist()->previous();
}
