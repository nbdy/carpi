//
// Created by insane on 13.08.20.
//

#include "VideoSettings.h"

VideoSettings::VideoSettings(QObject *parent) : RSettingsQT(parent) {

}

VideoSettings::~VideoSettings() {

}

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
