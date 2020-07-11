//
// Created by insane on 24.02.19.
//

#include "Command.h"

Command::Command() {}

std::thread Command::run(const std::string& cmd) {
    return std::thread([&](){system(cmd.c_str());});
}