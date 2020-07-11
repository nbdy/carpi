//
// Created by insane on 02.02.19.
//

#ifndef CARPI_FMTX_H
#define CARPI_FMTX_H

#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstdarg>
#include <cstdint>
#include <cmath>
#include <ctime>
#include <csignal>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <sndfile.h>

// https://github.com/F5OEO/rpitx/blob/master/src/fm/pifm.c
// untested

#define	BUFFER_LEN	(1024 * 8)

class FMTX {
private:
    int fileFreqTiming;
    bool writeTone(double freq, uint32_t timing);

public:
    FMTX();

    bool transmit(std::string fp);

};


#endif //CARPI_FMTX_H
