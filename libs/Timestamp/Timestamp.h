//
// Created by insane on 31.01.19.
//

#ifndef CARPI_TIMESTAMP_H
#define CARPI_TIMESTAMP_H


#include <string>

class Timestamp {
public:
    static std::string generateTimestamp();
    static std::string generateTimestamp(std::string& name);
    static tm parseTimestamp(std::string& ts);
    static tm parseTimestamp(std::string& ts, std::string& name);

};


#endif //CARPI_TIMESTAMP_H
