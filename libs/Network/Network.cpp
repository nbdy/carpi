//
// Created by insane on 12.07.20.
//

#include "Network.h"

QNetworkInterface Network::findInterface(const QString& prefix) {
    for(const QNetworkInterface& i : QNetworkInterface::allInterfaces()){
        if(i.name().startsWith(prefix)) return i;
    }
    return QNetworkInterface();
}

QString Network::getIP(const QString &prefix) {
    auto nif = findInterface(prefix);
    if(nif.isValid() && !nif.addressEntries().isEmpty()) {
        return nif.addressEntries().first().ip().toString();
    }
    return "";
}

QString Network::getMAC(const QString &prefix) {
    auto nif = findInterface(prefix);
    if(nif.isValid()) return nif.hardwareAddress();
    return "";
}
