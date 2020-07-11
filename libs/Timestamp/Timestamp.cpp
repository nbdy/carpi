//
// Created by insane on 31.01.19.
//

#include "Timestamp.h"


std::string Timestamp::generateTimestamp(std::string &name) {
    return generateTimestamp() + name;
}

std::string Timestamp::generateTimestamp() {
    time_t rt;
    struct tm* ti;
    char b[80];
    time(&rt);
    ti = localtime(&rt);
    strftime(b, sizeof(b), "%d.%m.%Y-%H:%M:%S", ti);
    return std::string(b);
}

tm Timestamp::parseTimestamp(std::string& ts) {
    static tm tm;
    strptime(ts.c_str(), "%d.%m.%Y-%H:%M:%S", &tm);
    return tm;
}

tm Timestamp::parseTimestamp(std::string &ts, std::string &name) {
    std::string r = ts.substr(0, ts.size() - name.size());
    return parseTimestamp(r);
}