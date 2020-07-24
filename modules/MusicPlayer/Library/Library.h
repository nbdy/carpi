//
// Created by insane on 23.07.20.
//

#ifndef CARPI_QT_LIBRARY_H
#define CARPI_QT_LIBRARY_H

#include "../Player/Player.h"
#include "SongItem/SongItem.h"
#include "AlbumItem/AlbumItem.h"

#include <QDir>
#include <QWidget>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Library; }
QT_END_NAMESPACE

class Library : public QWidget {
Q_OBJECT
private:
    Ui::Library *ui;
    Player *player;

    QList<AlbumItem*> *selectedAlbums;

    void populateSongs();
    void populateAlbums();

    static QString getName();

private slots:
    void onSongSelected(QListWidgetItem *item);
    void onAlbumSelected(QListWidgetItem *item);

public:
    explicit Library(Player *player, QWidget *parent = nullptr);
    ~Library() override;
};


#endif //CARPI_QT_LIBRARY_H
