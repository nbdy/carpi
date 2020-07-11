//
// Created by insane on 29.01.19.
//

#include <iostream>
#include "Runnable.h"
#include "../Timestamp/Timestamp.h"

Runnable::Runnable() {}

void Runnable::run() {}

bool Runnable::getDoRun() {
    return doRun;
}

void Runnable::setDoRun(bool doRun) {
    this->doRun = doRun;
}

std::thread Runnable::getThread() {
    return std::thread([&] {this->run();});
}

std::string Runnable::getName() {
    return name;
}

void Runnable::stop() {
    this->doRun = false;
}

void Runnable::setName(const std::string &name) {
    this->name = name;
}