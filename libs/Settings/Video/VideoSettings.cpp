//
// Created by insane on 13.08.20.
//

#include "VideoSettings.h"

VideoSettings::VideoSettings(QObject *parent) : RSettingsQT(KEY_VIDEO_SETTINGS, parent) {}

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
    auto v = get(KEY_VOLUME).toInt();
    qDebug() << "getVolume: " << v;
    return v;
}

void VideoSettings::setVolume(int value) {
    set(KEY_VOLUME, value);
    emit volumeChanged(value);
}

void VideoSettings::messageReceived(const QString &channel, const QString &message) {
    qDebug() << "received" << message << "from" << channel;
}

void VideoSettings::setDefaultValues() {
    setDirectory(QStandardPaths::writableLocation(QStandardPaths::MoviesLocation));
    setVolume(24);
    setLastVideo("");
}

bool VideoSettings::valuesSet() {
    return exists(KEY_LAST_VIDEO) && exists(KEY_VOLUME) && exists(KEY_DIRECTORY);
}

void VideoSettings::newSubscription(const QString &channel) {
    qDebug() << "new subscription:" << channel;
}

void VideoSettings::pre_init() {
    QObject::connect(this, &RedisQT::subscribed, this, &VideoSettings::newSubscription);
    QObject::connect(this, &RedisQT::message, this, &VideoSettings::messageReceived);
}
