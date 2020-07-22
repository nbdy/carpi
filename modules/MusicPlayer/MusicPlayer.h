//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MUSICPLAYER_H
#define CARPI_QT_MUSICPLAYER_H

#define KEY_SETTINGS_DIRECTORY "directory"
#define KEY_SETTINGS_VOLUME "volume"
#define KEY_SETTINGS_SHUFFLE "shuffle"
#define KEY_SETTINGS_MUTE "mute"
#define KEY_SETTINGS_DEFAULT_ALBUM "defaultAlbum"
#define KEY_SETTINGS_PLAY_ON_START "playOnStart"
#define KEY_SETTINGS_PLAY_ALBUM_ON_START "albumOnStart"

#include "MusicPlayer_global.h"
#include "../../libs/ISettings/ISettings.h"
#include "../../libs/Logger/Logger.h"

#include <QDir>
#include <QString>
#include <QMainWindow>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaMetaData>

QT_BEGIN_NAMESPACE
namespace Ui { class MusicPlayer; }
QT_END_NAMESPACE

class MusicPlayer : public QMainWindow
{
Q_OBJECT
private:
    bool playing = false;
    Ui::MusicPlayer *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QSettings *settings;

    void createDefaultSettings();
    void loadSettings();

private slots:
    void playPauseClicked();
    void shuffleCheckedChanged();
    void muteCheckedChanged();
    void playOnStartCheckedChanged();
    void onNextSong();

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer() override;

    void loadAlbum(const QString& path);
};

extern "C" {
    MUSICPLAYER_EXPORT int getDefaultIndex();
    MUSICPLAYER_EXPORT char* getName();
    MUSICPLAYER_EXPORT QWidget* create();
};


#endif //CARPI_QT_MUSICPLAYER_H
