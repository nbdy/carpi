//
// Created by insane on 02.02.19.
//

#include "FMTX.h"
#include "../Utils/Utils.h"


FMTX::FMTX() {}


bool FMTX::writeTone(double freq, u_int32_t timing) {
    typedef struct {
        double freq;
        uint32_t waitForSample;
    } samplerf_t;
    samplerf_t rfSample;

    rfSample.freq = freq;
    rfSample.waitForSample = timing;
    return write(fileFreqTiming, &rfSample, sizeof(samplerf_t)) != sizeof(samplerf_t);
}


bool FMTX::transmit(std::string fp) {
    if(!Utils::endsWith(fp, ".wav")) return false;

    float data [2*BUFFER_LEN];
    SNDFILE	*infile;
    SF_INFO sfinfo;
    int readcount, nb_samples;
    char *outfilename;
    int k;
    float x;

    infile = sf_open(fp.c_str(), SFM_READ, &sfinfo);
    if(!infile) return false;
    if(sfinfo.samplerate != 48000) return false;
    fileFreqTiming = open(outfilename, O_WRONLY|O_CREAT, 0644);
    int e = 6000;
    while ((readcount = sf_read_float(infile, data, BUFFER_LEN))){
        nb_samples = readcount / sfinfo.channels;
        for(k = 0; k < nb_samples; k++){
            x = data[k*sfinfo.channels];
            if(sfinfo.channels == 2){
                x += data[k * sfinfo.channels + 1];
                x /= 2;
            }
            writeTone(x * e * 2.0, 1e9 / 48000.0);
        }
    }
    sf_close(infile);
    close(fileFreqTiming);
    return true;
}