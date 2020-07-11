//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MUSICPLAYER_H
#define CARPI_QT_MUSICPLAYER_H


#include "MusicPlayer_global.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MusicPlayer; }
QT_END_NAMESPACE

class MusicPlayer : public QMainWindow
{
Q_OBJECT
private:
    Ui::MusicPlayer *ui;

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer() override;
};

extern "C" {
MUSICPLAYER_EXPORT QString getName();
MUSICPLAYER_EXPORT QWidget* render();
};


#endif //CARPI_QT_MUSICPLAYER_H
