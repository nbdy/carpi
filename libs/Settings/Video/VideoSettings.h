//
// Created by insane on 13.08.20.
//

#ifndef CARPI_QML_VIDEOSETTINGS_H
#define CARPI_QML_VIDEOSETTINGS_H

#include <rsettingsqt/rsettingsqt.h>

#define KEY_VIDEO_SETTINGS "video/"
#define KEY_DIRECTORY "directory"
#define KEY_LAST_VIDEO "lastVideo"
#define KEY_VOLUME "volume"

class VideoSettings : public RSettingsQT {
Q_OBJECT
Q_PROPERTY(QString directory READ getDirectory WRITE setDirectory NOTIFY directoryChanged)
Q_PROPERTY(QString lastVideo READ getLastVideo WRITE setLastVideo NOTIFY lastVideoChanged)
Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit VideoSettings(QObject *parent = nullptr);
    ~VideoSettings() override;

    static void registerType(){
        qmlRegisterType<VideoSettings>("settings", 1, 0, "VideoSettings");
    }

    [[nodiscard]] QString getDirectory() const;
    void setDirectory(const QString& directory);

    [[nodiscard]] QString getLastVideo() const;
    void setLastVideo(const QString& lastVideo);

    [[nodiscard]] int getVolume() const;
    void setVolume(int value);

    void setDefaultValues() override;
    bool valuesSet() override;

public slots:
    void messageReceived(const QString& channel, const QString& message);
    void newSubscription(const QString &channel);

signals:
    void directoryChanged(const QString& directory);
    void lastVideoChanged(const QString& lastVideo);
    void volumeChanged(int volume);

protected:
    void pre_init() override;

    QString directory;
    QString lastVideo;
    int volume;
};


#endif //CARPI_QML_VIDEOSETTINGS_H
