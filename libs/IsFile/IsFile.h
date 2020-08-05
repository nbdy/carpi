//
// Created by insane on 05.08.20.
//

#ifndef CARPI_QML_ISFILE_H
#define CARPI_QML_ISFILE_H

#include <QObject>
#include <QFile>
#include <QUrl>

class IsFile : public QObject {
    Q_OBJECT
    Q_PROPERTY(QUrl file READ getFile WRITE setFile NOTIFY fileChanged)
    Q_PROPERTY(bool isFile READ isFile NOTIFY isFileChanged)

public:
    explicit IsFile(QObject* parent = nullptr);
    ~IsFile() override;

    QUrl getFile() const;
    void setFile(const QUrl& file);
    bool isFile() const;

    signals:
    void fileChanged();
    void isFileChanged();

private:
    QUrl file;
};


#endif //CARPI_QML_ISFILE_H
