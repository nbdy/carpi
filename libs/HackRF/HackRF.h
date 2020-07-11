//
// Created by insane on 02.05.19.
//

#ifndef CARPI_HACKRF_H
#define CARPI_HACKRF_H

#include <pstreams/pstream.h>

class HackRF {
public:
    HackRF();
    ~HackRF();

    int sweep(bool ampEnable, bool antennaEnable, int numSweeps, bool record, std::pair<int, int> minMaxFreq, int lna=-1, int gain=-1, int numSamples=-1, int binWidth=-1);

private:
    bool doRun;
};


#endif //CARPI_HACKRF_H
