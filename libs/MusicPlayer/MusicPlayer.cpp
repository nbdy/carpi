//
// Created by insane on 04.02.19.
//

#include <iostream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <fstream>
#include "MusicPlayer.h"
#include "../Utils/Utils.h"


MusicPlayer::MusicPlayer(MusicLibrary *library) {
    this->library = library;
    setDoRun(true);
    ao_initialize();
    format = ao_sample_format();
    format.bits = 16;
    format.channels = 2;
    format.rate = 44100;
    format.byte_format = AO_FMT_NATIVE;
    device = ao_open_live(ao_default_driver_id(), &format, nullptr);
    eq = new Equalizer();
}

MusicPlayer::~MusicPlayer() {
    ao_close(device);
    ao_shutdown();
};

void MusicPlayer::_setVolume(mpg123_handle *mh) {
    volumeMtx.lock();
    if(shouldSetVolume){
        mpg123_volume(mh, volume);
        shouldSetVolume = false;
    }
    volumeMtx.unlock();
}

void MusicPlayer::_setPosition(mpg123_handle *mh) {
    positionMtx.lock();
    if(shouldSetPosition){
        mpg123_seek(mh, position, SEEK_SET); // whence	one of SEEK_SET, SEEK_CUR or SEEK_END
        shouldSetPosition = false;
    }
    position = mpg123_tell(mh);
    positionMtx.unlock();
}

void MusicPlayer::playSong(std::string song) {
    int error = mpg123_init();
    unsigned char* buffer = nullptr;
    int channels = 0;
    int encoding = 0;
    long rate = 0;
    size_t buffer_size = 0;
    size_t done = 0;
    off_t samples = 0;
    int framesize = 1;
    mpg123_handle *mh = nullptr;
    if(error != MPG123_OK || (mh = mpg123_new(nullptr, &error)) == nullptr){
        fprintf(stderr, "Basic setup goes wrong: %s", mpg123_plain_strerror(error));
    }
    if(mpg123_open(mh, song.c_str()) != MPG123_OK || mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK ){
        std::cout << "could not load information: " << song << std::endl;
    }
    mpg123_format_none(mh);
    mpg123_format(mh, rate, channels, encoding);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*) malloc( buffer_size );
    lengthMtx.lock();
    length = mpg123_length(mh);
    lengthMtx.unlock();
    history.emplace_back(currentSong);
    do {
        if(shouldSkip){
            skipMtx.lock();
            shouldSkip = false;
            skipMtx.unlock();
            error = MPG123_DONE;
            break;
        }

        _setPosition(mh);
        _setVolume(mh);

        while(shouldBePaused){
            pauseMtx.lock();
            isPaused = true;
            pauseMtx.unlock();

            _setVolume(mh);
            _setPosition(mh);

            usleep(420); // be nice
        }

        eq->apply(mh);

        pauseMtx.lock();
        isPaused = false;
        pauseMtx.unlock();

        playMtx.lock();
        isPlaying = true;
        playMtx.unlock();

        size_t played;
        error = mpg123_read( mh, buffer, buffer_size, &done );
        ao_play(device, (char*)buffer, buffer_size);
        samples += played/framesize;
    } while(done && error==MPG123_OK && shouldBePlaying);
    playMtx.lock();
    isPlaying = false;
    playMtx.unlock();
    free(buffer);
    if(error != MPG123_DONE) fprintf( stderr, "Warning: Decoding ended prematurely because: %s\n",  error == MPG123_ERR ? mpg123_strerror(mh) : mpg123_plain_strerror(error) );
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    if(shouldBePlaying) {
        if(history.size() >= dontRepeatThreshold) history.clear();
        currentSong = library->getRandomSong();
        if(dontRepeat){while(Utils::contains(history, currentSong)) currentSong = library->getRandomSong();}
        playSong(currentSong);
    }
}

void MusicPlayer::run() {
    currentSong = library->getRandomSong();
    while(getDoRun()){
        if(shouldBePlaying && !isPlaying) playSong(currentSong);
        usleep(1420);
    }
}

void MusicPlayer::play() {
    shouldBePlaying = true;
    shouldBePaused = false;
}

void MusicPlayer::pause() {
    shouldBePaused = !isPaused;
}

void MusicPlayer::playPause() {
    if(!isPlaying) play();
    else pause();
}

void MusicPlayer::stop() {
    shouldBePlaying = false;
}

void MusicPlayer::next() {
    bool wasPaused = isPaused;
    if(isPaused) shouldBePaused = false;
    skipMtx.lock();
    shouldSkip = true;
    skipMtx.unlock();
    shouldBePlaying = true;
    shouldBePaused = wasPaused;
}

SongInformation MusicPlayer::getCurrentSong() {
    return library->getSongInformation(currentSong);
}

bool MusicPlayer::getIsPlaying() {
    return isPlaying;
}

bool MusicPlayer::getIsPaused() {
    return isPaused;
}

void MusicPlayer::setVolume(double value) {
    volumeMtx.lock();
    volume = value;
    shouldSetVolume = true;
    volumeMtx.unlock();
}

double MusicPlayer::getVolume() {
    return volume;
}

off_t MusicPlayer::getPosition() {
    positionMtx.lock();
    off_t r = position;
    positionMtx.unlock();
    return r;
}

void MusicPlayer::setPosition(off_t position) {
    positionMtx.lock();
    this->position = position;
    shouldSetPosition = true;
    positionMtx.unlock();
}

off_t MusicPlayer::getLength() {
    lengthMtx.lock();
    off_t r = length;
    lengthMtx.unlock();
    return r;
}

Equalizer::Equalizer() {

}

void Equalizer::apply(mpg123_handle *mh) {
    for(auto& e : values.items()){
        mpg123_eq(mh, MPG123_LEFT|MPG123_RIGHT, atoi(e.key().c_str()), e.value());
    }
}

void Equalizer::setBand(int channel, double value) {
    values[channel] = value;
}

bool MusicPlayer::getDontRepeat() {return dontRepeat;}

void MusicPlayer::setDontRepeat(bool value) {this->dontRepeat = value;}

MusicPlayer::MusicPlayer(MusicLibrary *library, int dontRepeatThreshold) {
    this->library = library;
    this->dontRepeatThreshold = dontRepeatThreshold;
}