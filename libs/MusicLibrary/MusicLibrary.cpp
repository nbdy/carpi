//
// Created by insane on 02.02.19.
//

#include "MusicLibrary.h"
#include "../Utils/Utils.h"
#include <random>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>


// expecting
// artist - albums - songs
// ex: Korn/The Serenity of Suffering [Explicit]/02 - Rotting In Vain [Explicit].mp3
MusicLibrary::MusicLibrary() {
    if(Utils::isPi()){
        path = "/home/pi/Music/";
    } else {
        path = "/home/insane/Music/";
    }
    if(!Utils::isDirectory(path)) mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
    buildLibrary();
}

MusicLibrary::MusicLibrary(const std::string& path) {
    this->path = path;
    buildLibrary();
}

std::string MusicLibrary::getRandomSong() {
    if(songs.empty()) return "";
    if(songs.size() == 1) return songs[0];
    return songs[random() % (songs.size() - 1)];
}

void MusicLibrary::buildLibrary() {
    for(const std::string& artist : Utils::listDirectory(path, false)){
        std::string ap = path + artist + "/";
        library[artist] = {};
        //std::cout << ap << std::endl;
        for(const std::string& album : Utils::listDirectory(ap, false)){
            std::string aap = ap + album + "/";
            library[artist][album] = std::vector<std::string>{};
            //std::cout << "\t" << aap << std::endl;
            for(const std::string& song : Utils::listDirectory(aap, false)){
                std::string sng = aap + song.substr(0, song.size());
                //std::cout << "\t\t" << song << std::endl;
                library[artist][album].emplace_back(sng);
                songs.emplace_back(sng);
            }
        }
    }
    std::cout << library << std::endl;
}

SongInformation MusicLibrary::getSongInformation(std::string songPath) {
    songPath = Utils::replaceAll(std::move(songPath), path, "");
    std::vector<std::string> tmp = Utils::split(songPath, '/');
    // for(const std::string& i : tmp) std::cout << i << std::endl;
    SongInformation si;
    si.artist = tmp[0];
    si.album = tmp[1];
    si.title = Utils::replaceAll(songPath, tmp[0] + "/" + tmp[1] + "/", "");
    return si;
}