//
// Created by insane on 29.01.19.
//

#ifndef CARPI_RUNNABLE_H
#define CARPI_RUNNABLE_H

#include <thread>

#include "../Json/json.hpp"

using nlohmann::json;

class Runnable {
private:
    std::string name = "Runnable";
    bool doRun = false;

public:
    Runnable();

    virtual void run();
    virtual void stop();

    bool getDoRun();
    void setDoRun(bool doRun);

    std::string getName();
    void setName(const std::string& name);

    std::thread getThread();
};


#endif //CARPI_RUNNABLE_H
