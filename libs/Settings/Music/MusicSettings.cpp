//
// Created by insane on 13.08.20.
//

#include "MusicSettings.h"

MusicSettings::MusicSettings(QObject *parent) : RSettingsQT(KEY_MUSIC_SETTINGS, parent) {
    QObject::connect(this, &RedisQT::message, this, &MusicSettings::messageReceived);
    init();
}

MusicSettings::~MusicSettings() = default;

void MusicSettings::setDirectory(const QString &value) {
    set(KEY_DIRECTORY, value);
    emit directoryChanged(value);
}

QString MusicSettings::getDirectory() const {
    return directory;
}

void MusicSettings::setLastAlbum(const QString &value) {
    set(KEY_LAST_ALBUM, value);
    emit lastAlbumChanged(value);
}

QString MusicSettings::getLastAlbum() const {
    return lastAlbum;
}

void MusicSettings::setLastSong(const QString &value) {
    set(KEY_LAST_SONG, value);
    emit lastSongChanged(value);
}

QString MusicSettings::getLastSong() const {
    return lastSong;
}

void MusicSettings::setVolume(int value) {
    set(KEY_VOLUME, value);
    emit volumeChanged(value);
}

int MusicSettings::getVolume() const {
    return volume;
}

void MusicSettings::setDefaultValues() {
    qDebug() << "setDefaultValues";
    setDirectory(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
    setVolume(42);
    setLastAlbum("");
    setLastSong("");
}

bool MusicSettings::valuesSet() {
    return exists(KEY_DIRECTORY) && exists(KEY_LAST_ALBUM) && exists(KEY_LAST_SONG) && exists(KEY_VOLUME);
}

void MusicSettings::messageReceived(const QString &channel, const QString &message) {
    auto doc = str2doc(message.toStdString());
    if(!doc[KEY_LAST_ALBUM].isUndefined()) lastAlbum = doc[KEY_LAST_ALBUM].toString();
    else if(!doc[KEY_DIRECTORY].isUndefined()) directory = doc[KEY_DIRECTORY].toString();
    else if(!doc[KEY_VOLUME].isUndefined()) volume = doc[KEY_VOLUME].toInt();
    else if(!doc[KEY_LAST_SONG].isUndefined()) lastSong = doc[KEY_LAST_SONG].toString();
}

void MusicSettings::setValues() {
    directory = get(KEY_DIRECTORY).toString();
    lastSong = get(KEY_LAST_SONG).toString();
    lastAlbum = get(KEY_LAST_ALBUM).toString();
    volume = get(KEY_VOLUME).toInt();
}
