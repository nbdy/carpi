//
// Created by insane on 04.05.19.
//

#include <iostream>
#include "Subprocess.h"

Subprocess::Subprocess() {}

Subprocess::Subprocess(const std::string &command) {
    this->command = command;
}

Subprocess::~Subprocess() {}

bool Subprocess::isRunning() {
    return running;
}

void Subprocess::setCommand(const std::string &command) {this->command = command;}

std::string Subprocess::getCommand() {return command;}

std::vector<std::string> Subprocess::getLog() {
    return log;
}

void Subprocess::start() {
    redi::ipstream i(command);
    std::string line;
    running = true;
    while(std::getline(i, line)){
        log.emplace_back(line);
        if(i.eof()) break;
    }
    running = false;
    i.close();
}
