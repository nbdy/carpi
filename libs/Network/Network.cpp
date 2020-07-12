//
// Created by insane on 12.07.20.
//

#include "Network.h"

const QNetworkInterface* Network::findInterface(const QString& prefix) {
    qDebug() << "trying to find interface with prefix" << prefix;
    for(const QNetworkInterface& i : QNetworkInterface::allInterfaces()){
        if(i.name().startsWith(prefix)) return &i;
    }
    return nullptr;
}

QString Network::getIP(const QString &prefix) {
    auto *nif = findInterface(prefix);
    return nif->addressEntries().first().ip().toString();
}

QString Network::getMAC(const QString &prefix) {
    auto *nif = findInterface(prefix);
    return nif->hardwareAddress();
}
