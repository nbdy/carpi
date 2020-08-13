//
// Created by insane on 13.08.20.
//

#include "MusicSettings.h"

MusicSettings::MusicSettings(QObject *parent) : RSettingsQT(parent) {

}

MusicSettings::~MusicSettings() {

}

void MusicSettings::setDirectory(const QString &directory) {
    set(KEY_DIRECTORY, directory);
    emit directoryChanged(directory);
}

QString MusicSettings::getDirectory() const {
    return get(KEY_DIRECTORY).toString();
}

void MusicSettings::setLastAlbum(const QString &lastAlbum) {
    set(KEY_LAST_ALBUM, lastAlbum);
    emit lastAlbumChanged(lastAlbum);
}

QString MusicSettings::getLastAlbum() const {
    return get(KEY_LAST_ALBUM).toString();
}

void MusicSettings::setLastSong(const QString &lastSong) {
    set(KEY_LAST_SONG, lastSong);
    emit lastSongChanged(lastSong);
}

QString MusicSettings::getLastSong() const {
    return get(KEY_LAST_SONG).toString();
}

void MusicSettings::setVolume(int value) {
    set(KEY_VOLUME, value);
    emit volumeChanged(value);
}

int MusicSettings::getVolume() const {
    return get(KEY_VOLUME).toInt();
}