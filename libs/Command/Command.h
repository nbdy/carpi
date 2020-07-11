//
// Created by insane on 24.02.19.
//

#ifndef CARPI_COMMAND_H
#define CARPI_COMMAND_H


#include "../Runnable/Runnable.h"

class Command {
public:
    Command();

    static std::thread run(const std::string& cmd);
};


#endif //CARPI_COMMAND_H
