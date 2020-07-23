//
// Created by insane on 11.07.20.
//

#ifndef CARPI_QT_MUSICPLAYER_H
#define CARPI_QT_MUSICPLAYER_H

#include "MusicPlayer_global.h"
#include "../../libs/ISettings/ISettings.h"
#include "../../libs/Logger/Logger.h"

#include "Player/Player.h"


#include <QString>
#include <QWidget>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MusicPlayer; }
QT_END_NAMESPACE

class MusicPlayer : public QWidget
{
Q_OBJECT
private:
    Ui::MusicPlayer *ui;
    QGridLayout *playerLayout;

    Player *player;

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer() override;
};

extern "C" {
    MUSICPLAYER_EXPORT int getDefaultIndex();
    MUSICPLAYER_EXPORT char* getName();
    MUSICPLAYER_EXPORT QWidget* create();
};


#endif //CARPI_QT_MUSICPLAYER_H
