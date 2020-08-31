//
// Created by insane on 13.08.20.
//

#ifndef CARPI_QML_MUSICSETTINGS_H
#define CARPI_QML_MUSICSETTINGS_H

#include <rsettingsqt/rsettingsqt.h>

#define KEY_MUSIC_SETTINGS "music/"
#define KEY_DIRECTORY "directory"
#define KEY_LAST_ALBUM "lastAlbum"
#define KEY_LAST_SONG "lastSong"
#define KEY_VOLUME "volume"

class MusicSettings : public RSettingsQT {
Q_OBJECT

Q_PROPERTY(QString directory READ getDirectory WRITE setDirectory NOTIFY directoryChanged)
Q_PROPERTY(QString lastAlbum READ getLastAlbum WRITE setLastAlbum NOTIFY lastAlbumChanged)
Q_PROPERTY(QString lastSong READ getLastSong WRITE setLastSong NOTIFY lastSongChanged)
Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit MusicSettings(QObject *parent = nullptr);
    ~MusicSettings() override;

    static void registerType(){
        qmlRegisterType<MusicSettings>("settings", 1, 0, "MusicSettings");
    }

    void setDirectory(const QString& directory);
    [[nodiscard]] QString getDirectory() const;

    void setLastAlbum(const QString& lastAlbum);
    [[nodiscard]] QString getLastAlbum() const;

    void setLastSong(const QString& lastSong);
    [[nodiscard]] QString getLastSong() const;

    void setVolume(int value);
    [[nodiscard]] int getVolume() const;

    void setDefaultValues() override;
    bool valuesSet() override;
    void setValues();


public slots:
    void messageReceived(const QString& channel, const QString& message);

signals:
    void directoryChanged(const QString& directory);
    void lastAlbumChanged(const QString& lastAlbum);
    void lastSongChanged(const QString& lastSong);
    void volumeChanged(int volume);

protected:
    QString directory;
    QString lastAlbum;
    QString lastSong;
    int volume;
};


#endif //CARPI_QML_MUSICSETTINGS_H
