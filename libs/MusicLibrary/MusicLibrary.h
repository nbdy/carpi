//
// Created by insane on 02.02.19.
//

#ifndef CARPI_MUSICLIBRARY_H
#define CARPI_MUSICLIBRARY_H


#include <string>
#include <vector>

#include "../Json/json.hpp"

using nlohmann::json;

struct SongInformation {
    std::string title;
    std::string artist;
    std::string album;
};

class MusicLibrary {
private:
    std::string path;
    json library;
    std::vector<std::string> songs;

    void buildLibrary();

public:
    MusicLibrary();
    explicit MusicLibrary(const std::string& path);

    std::string getRandomSong();
    SongInformation getSongInformation(std::string songPath);
};


#endif //CARPI_MUSICLIBRARY_H
