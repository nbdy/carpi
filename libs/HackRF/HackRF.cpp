//
// Created by insane on 02.05.19.
//

#include "HackRF.h"


HackRF::HackRF() {

}

HackRF::~HackRF() {

}

int HackRF::sweep(bool ampEnable, bool antennaEnable, int numSweeps, bool record, std::pair<int, int> minMaxFreq, int lna=-1, int gain=-1, int numSamples=-1, int binWidth=-1) {
    std::string cmd = "hackrf_sweep ";
    if(ampEnable) cmd += "-a 1 ";
    else cmd += "-a 0 ";
    if(antennaEnable) cmd += "-p 1 ";
    else cmd += "-p 0 ";
    if(minMaxFreq.first != -1 && minMaxFreq.second != -1) cmd += "-f " + std::to_string(minMaxFreq.first) + ":" + std::to_string(minMaxFreq.second) + " ";
    if(lna != -1) cmd += "-l " + std::to_string(lna) + " ";
    if(lna != -1) cmd += "-g " + std::to_string(gain) + " ";
    if(numSamples != -1) cmd += "-n " + std::to_string(numSamples) + " ";
    if(binWidth != -1) cmd += "-w " + std::to_string(binWidth) + " ";
    cmd += "-N " + std::to_string(numSweeps) + " ";
    if(record) cmd += "-r output.hackrf "; // todo write to file and save name as id in database
}