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

    void createDefaultSettings();
    void loadSettings();

    QString getName();

    template<typename T> void setValue(const QString& key, T value);

private slots:
    void nextClicked();
    void previousClicked();
    void playPauseClicked();
    void onSongPositionSliderChanged(int pos);
    void onVolumeValueSliderChanged(int pos);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void shuffleCheckedChanged();
    void muteCheckedChanged();
    void playOnStartCheckedChanged();
    void onNextSong();
    void handleMediaPlayerError();
    void handleMediaPlayerMediaStatusChanged();
    void handleMediaPlayerStateChanged();

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player() override;

    QMediaPlayer* getMediaPlayer();
    QString getMusicDirectory();
};


#endif //CARPI_QT_PLAYER_H
