//
// Created by insane on 04.02.19.
//

#ifndef CARPI_MUSICPLAYER_H
#define CARPI_MUSICPLAYER_H

#include <unistd.h>
#include <ao/ao.h>
#include <string>
#include <cstdio>
#include <mutex>
#include "../MusicLibrary/MusicLibrary.h"
#include "../Runnable/Runnable.h"

#include <mpg123.h>

class Equalizer {
private:
    nlohmann::json values;

public:
    Equalizer();

    void setBand(int channel, double value);
    void apply(mpg123_handle *mh);
};

class MusicPlayer : public Runnable {
private:
    bool dontRepeat = true;

    Equalizer *eq;

    std::mutex skipMtx;
    bool shouldSkip = false;

    std::mutex playMtx;
    bool shouldBePlaying = false;
    bool isPlaying = false;

    std::mutex pauseMtx;
    bool shouldBePaused = false;
    bool isPaused = false;

    std::mutex volumeMtx;
    bool shouldSetVolume = false;
    double volume = 4.2;

    std::mutex positionMtx;
    bool shouldSetPosition = false;
    off_t position = 0;

    std::mutex lengthMtx;
    off_t length = 0;

    std::string currentSong;
    MusicLibrary *library;
    std::vector<std::string> history;
    int dontRepeatThreshold = 50;

    ao_device *device;
    ao_sample_format format;

    void playSong(std::string song);
    void _setVolume(mpg123_handle* mh);
    void _setPosition(mpg123_handle* mh);
public:
    explicit MusicPlayer(MusicLibrary *library);
    MusicPlayer(MusicLibrary * library, int dontRepeatThreshold);
    ~MusicPlayer();

    SongInformation getCurrentSong();
    void run() override;
    void stop() override;
    void next();
    void playPause();
    void play();
    void pause();
    void setVolume(double value);
    double getVolume();
    off_t getPosition();
    void setPosition(off_t position);
    off_t getLength();

    void setDontRepeat(bool value);
    bool getDontRepeat();

    bool getIsPlaying();
    bool getIsPaused();
};


#endif //CARPI_MUSICPLAYER_H
