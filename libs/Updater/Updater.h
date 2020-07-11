//
// Created by insane on 14.02.19.
//

#ifndef CARPI_UPDATER_H
#define CARPI_UPDATER_H


#include <string>
#include <unistd.h>
#include <sys/reboot.h>
#include "../Runnable/Runnable.h"
#include "../Configuration/Configuration.h"

class Updater : public Runnable {
private:
    uc::UpdaterConfiguration uc;
    int progress;
    std::vector<std::string> output;

public:
    explicit Updater(const uc::UpdaterConfiguration& uc);
    void run() override;
    int getProgress();
    std::vector<std::string> getOutput();
};


#endif //CARPI_UPDATER_H
