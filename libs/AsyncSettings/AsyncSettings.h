//
// Created by insane on 06.08.20.
//

#ifndef CARPI_QML_ASYNCSETTINGS_H
#define CARPI_QML_ASYNCSETTINGS_H

#include <QObject>
#include <QSettings>

class AsyncSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString group READ getGroup WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(QString organizationName READ getOrganizationName WRITE setOrganizationName NOTIFY organizationNameChanged)
    Q_PROPERTY(QString applicationName READ getApplicationName WRITE setApplicationName NOTIFY applicationNameChanged)

public:
    explicit AsyncSettings(QObject *parent = nullptr);
    ~AsyncSettings() override;

    Q_INVOKABLE void setValue(const QString& key, const QVariant& value);
    Q_INVOKABLE QVariant getValue(const QString& key) const;

    void setGroup(const QString& group);
    QString getGroup() const;

    void setOrganizationName(const QString& name);
    QString getOrganizationName() const;

    void setApplicationName(const QString& name);
    QString getApplicationName() const;

signals:
    void valueChanged(const QString& key, const QVariant& value);
    void groupChanged();
    void organizationNameChanged();
    void applicationNameChanged();
    void settingsReady();

private:
    void _createSettings();

    QString group;
    QString organizationName = "";
    QString applicationName = "";

    QSettings *settings;
};


#endif //CARPI_QML_ASYNCSETTINGS_H
