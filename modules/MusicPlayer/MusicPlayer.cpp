//
// Created by insane on 11.07.20.
//

#include "MusicPlayer.h"
#include "ui_musicplayer.h"

// todo lst_albums populate; select and only load selected albums

MusicPlayer::MusicPlayer(QWidget *parent): QMainWindow(parent), ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);

    connect(ui->playPause, SIGNAL(clicked()), this, SLOT(playPauseClicked()));

    connect(ui->cb_shuffle, SIGNAL(stateChanged(int)), this, SLOT(shuffleCheckedChanged()));
    connect(ui->cb_mute, SIGNAL(stateChanged(int)), this, SLOT(muteCheckedChanged()));
    connect(ui->cb_play_on_start, SIGNAL(stateChanged(int)), this, SLOT(playOnStartCheckedChanged()));

    connect(ui->next, SIGNAL(clicked()), playlist, SLOT(next()));
    connect(ui->previous, SIGNAL(clicked()), playlist, SLOT(previous()));

    connect(ui->sldr_song, SIGNAL(valueChanged(int)), this, SLOT(onSongPositionSliderChanged(int)));
    connect(ui->sldr_volume, SIGNAL(valueChanged(int)), this, SLOT(onVolumeValueSliderChanged(int)));

    connect(player, SIGNAL(mediaChanged(const QMediaContent&)), this, SLOT(onNextSong()));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64))); // ^

    settings = ISettings::getSettings(this);
    createDefaultSettings();
    loadSettings();
}

MusicPlayer::~MusicPlayer()
{
    settings->endGroup();
    settings->sync();
    delete settings;
    delete playlist;
    delete player;
    delete ui;
}

void MusicPlayer::createDefaultSettings() {
    if(!settings->contains(getName())) return;
    Logger::info(getName(), "setting default settings");
    settings->beginGroup(getName());
    settings->setValue(KEY_SETTINGS_DIRECTORY, "~/Music/");
    settings->setValue(KEY_SETTINGS_VOLUME, 30);
    settings->setValue(KEY_SETTINGS_SHUFFLE, false);
    settings->setValue(KEY_SETTINGS_PLAY_ALBUM_ON_START, false); // todo actually use this
    settings->setValue(KEY_SETTINGS_PLAY_ON_START, false);
    settings->setValue(KEY_SETTINGS_DEFAULT_ALBUM, "");
}

void MusicPlayer::loadSettings() {
    Logger::info(getName(), "loading settings");

    bool muted = settings->value(KEY_SETTINGS_MUTE).toBool();
    player->setMuted(muted);
    ui->cb_mute->setChecked(muted);

    ui->cb_shuffle->setChecked(settings->value(KEY_SETTINGS_SHUFFLE).toBool());

    int volume = settings->value(KEY_SETTINGS_VOLUME).toInt();
    ui->sldr_volume->setValue(volume);
    player->setVolume(volume);

    QString defaultAlbum = settings->value(KEY_SETTINGS_DEFAULT_ALBUM).toString();
    if(defaultAlbum != "") loadAlbum(defaultAlbum);

}

void MusicPlayer::loadAlbum(const QString& path) {
    if(!playlist->clear()) Logger::warning(getName(), "could not clear playlist"); // todo inform ui
    QDir albumDirectory(path);
    Logger::info(getName(), "populating playlist from '" + albumDirectory.absolutePath() + "'");
    for(const QString& fp : albumDirectory.entryList(QStringList() << "*.mp3" << "*.wav", QDir::Files)) {
        QString afp = albumDirectory.absoluteFilePath(fp);
        Logger::debug(getName(), "adding '" + afp + "' to current playlist");
        playlist->addMedia(QUrl::fromLocalFile(afp));
    }
}

void MusicPlayer::playPauseClicked() {
    if(playing) player->pause();
    else player->play();
}

void MusicPlayer::shuffleCheckedChanged() {
    settings->setValue(KEY_SETTINGS_SHUFFLE, ui->cb_shuffle->isChecked()); // todo actually shuffle when enabled
}

void MusicPlayer::muteCheckedChanged() {
    bool muted = ui->cb_mute->isChecked();
    settings->setValue(KEY_SETTINGS_MUTE, muted);
    player->setMuted(muted);
}

void MusicPlayer::onNextSong() {
    // todo implement shuffle here
    ui->lbl_artist->setText(player->metaData(QMediaMetaData::AlbumArtist).toString());
    ui->lbl_album->setText(player->metaData(QMediaMetaData::AlbumTitle).toString());
    ui->lbl_song->setText(player->metaData(QMediaMetaData::Title).toString());
    // todo use player->metaData(QMediaMetaData::CoverArtImage);
}

void MusicPlayer::playOnStartCheckedChanged() {
    settings->setValue(KEY_SETTINGS_PLAY_ON_START, ui->cb_play_on_start->isChecked());
}

void MusicPlayer::onSongPositionSliderChanged(int pos) {
    player->setPosition(pos);
}

void MusicPlayer::onVolumeValueSliderChanged(int pos) {
    settings->setValue(KEY_SETTINGS_VOLUME, pos);
    player->setVolume(pos);
}

void MusicPlayer::onDurationChanged(qint64 duration) {
    ui->lbl_max_position->setText(QString::number(duration)); // todo convert to mm:ss
}

void MusicPlayer::onPositionChanged(qint64 position) {
    ui->lbl_current_position->setText(QString::number(position)); // todo convert to mm:ss
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