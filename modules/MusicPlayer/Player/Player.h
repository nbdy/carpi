//
// Created by insane on 23.07.20.
//

#ifndef CARPI_QT_PLAYER_H
#define CARPI_QT_PLAYER_H

#include "../../../libs/ISettings/ISettings.h"
#include "../../../libs/Logger/Logger.h"

#include <QDir>
#include <QWidget>

#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaMetaData>

#define KEY_SETTINGS_DIRECTORY "directory"
#define KEY_SETTINGS_VOLUME "volume"
#define KEY_SETTINGS_SHUFFLE "shuffle"
#define KEY_SETTINGS_MUTE "mute"
#define KEY_SETTINGS_DEFAULT_ALBUM "defaultAlbum"
#define KEY_SETTINGS_PLAY_ON_START "playOnStart"
#define KEY_SETTINGS_PLAY_ALBUM_ON_START "albumOnStart"

QT_BEGIN_NAMESPACE
namespace Ui { class Player; }
QT_END_NAMESPACE

class Player : public QWidget {
Q_OBJECT
private:
    Ui::Player *ui;

    QSettings *settings;

    bool playing = false;

    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    void createDefaultSettings();
    void loadSettings();

    QString getName();
    void loadAlbum(const QString& path);

    template<typename T> void setValue(const QString& key, T value);

private slots:
    void playPauseClicked();
    void onSongPositionSliderChanged(int pos);
    void onVolumeValueSliderChanged(int pos);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void shuffleCheckedChanged();
    void muteCheckedChanged();
    void playOnStartCheckedChanged();
    void onNextSong();

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player() override;
};


#endif //CARPI_QT_PLAYER_H
