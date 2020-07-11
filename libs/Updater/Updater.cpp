//
// Created by insane on 14.02.19.
//

#include <iostream>
#include "Updater.h"
#include "../Subprocess/Subprocess.h"

Updater::Updater(const uc::UpdaterConfiguration& uc) {
    setDoRun(true);
    progress = 0;
    this->uc = uc;
}

void Updater::run() {
    if (Utils::isPi() && getDoRun()) {
        std::vector<Subprocess*> steps;
        if(!Utils::endsWith(uc.path, "/")) uc.path += "/";
        std::string psc = "cd " + uc.path + "carpi ; ";
        if(!Utils::isDirectory(uc.path + "carpi")){
            steps.emplace_back(new Subprocess("cd " + uc.path + " ; sudo -u pi git clone " + uc.url + " carpi"));
        } else {
            steps.emplace_back(new Subprocess(psc + "git pull ; git submodule update --recursive --remote"));
        }
        steps.emplace_back(new Subprocess(psc + "rm -rf build ; mkdir build ; cd build ; cmake .."));
        steps.emplace_back(new Subprocess(psc + "cd build ; sudo killall carpi ; make -j4 ; sudo carpi"));
        progress = 0;
        float progressSteps = 100 / steps.size();
        float left = 100 % steps.size();
        for(Subprocess* p : steps) {
            std::cout << "[updater] running " << p->getCommand() << std::endl;
            output.emplace_back(p->getCommand());
            p->start();
            while(p->isRunning()){
                sleep(2);
                for(const std::string& l : p->getLog()) {
                    std::cout << l << std::endl;
                    output.emplace_back(l);
                }
            }
            progress += progressSteps;
        }
        progress += left;
        sync();
    } else {
        progress = -1;
        std::cout << "updater: you probably dont want this" << std::endl;
    }
}

int Updater::getProgress() {
    return progress;
}

std::vector<std::string> Updater::getOutput() {return output;}