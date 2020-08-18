//
// Created by insane on 13.08.20.
//

#include "VideoSettings.h"

VideoSettings::VideoSettings(QObject *parent) : RSettingsQT(KEY_VIDEO_SETTINGS, parent) {
    QObject::connect(this, &RedisQT::ready, this, &VideoSettings::readyReceived);
    QObject::connect(this, &RedisQT::message, this, &VideoSettings::messageReceived);
    init();
}

VideoSettings::~VideoSettings() {}

QString VideoSettings::getDirectory() const {
    return get(KEY_DIRECTORY).toString();
}

void VideoSettings::setDirectory(const QString &directory) {
    set(KEY_DIRECTORY, directory);
    emit directoryChanged(directory);
}

QString VideoSettings::getLastVideo() const {
    return get(KEY_LAST_VIDEO).toString();
}

void VideoSettings::setLastVideo(const QString &lastVideo) {
    set(KEY_LAST_VIDEO, lastVideo);
    emit lastVideoChanged(lastVideo);
}

int VideoSettings::getVolume() const {
    return get(KEY_VOLUME).toInt();
}

void VideoSettings::setVolume(int value) {
    set(KEY_VOLUME, value);
    emit volumeChanged(value);
}

void VideoSettings::messageReceived(const QString &channel, const QString &message) {
    auto doc = str2doc(message.toStdString());
    if(!doc[KEY_DIRECTORY].isUndefined()) directory = doc[KEY_DIRECTORY].toString();
    else if(!doc[KEY_LAST_VIDEO].isUndefined()) lastVideo = doc[KEY_LAST_VIDEO].toString();
    else if(!doc[KEY_VOLUME].isUndefined()) volume = doc[KEY_VOLUME].toInt();
}

void VideoSettings::setDefaultValues() {
    setDirectory(QStandardPaths::writableLocation(QStandardPaths::MoviesLocation));
    setVolume(24);
    setLastVideo("");
}

bool VideoSettings::valuesSet() {
    return exists(KEY_LAST_VIDEO) && exists(KEY_VOLUME) && exists(KEY_DIRECTORY);
}

void VideoSettings::setValues() {
    volume = get(KEY_VOLUME).toInt();
    directory = get(KEY_DIRECTORY).toString();
    lastVideo = get(KEY_LAST_VIDEO).toString();
}
