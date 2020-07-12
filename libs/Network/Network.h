//
// Created by insane on 12.07.20.
//

#ifndef CARPI_QT_NETWORK_H
#define CARPI_QT_NETWORK_H

#include <QtNetwork/QNetworkInterface>
#include <QString>
#include <QPair>

class Network {
public:
    static QNetworkInterface findInterface(const QString& prefix);
    static QString getIP(const QString& prefix);
    static QString getMAC(const QString& prefix);
};


#endif //CARPI_QT_NETWORK_H
