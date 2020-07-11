//
// Created by insane on 04.05.19.
//

#ifndef CARPI_SUBPROCESS_H
#define CARPI_SUBPROCESS_H


#include <string>
#include <vector>
#include <pstreams/pstream.h>

class Subprocess {
public:
    Subprocess();
    explicit Subprocess(const std::string& command);
    ~Subprocess();

    std::vector<std::string> getLog();
    std::string getCommand();
    void setCommand(const std::string& command);
    bool isRunning();
    virtual void start();

private:
    bool running = false;
    std::string command;
    std::vector<std::string> log;
};


#endif //CARPI_SUBPROCESS_H
