//
// Created by insane on 02.02.19.
//

#include <dirent.h>
#include "Utils.h"
#include <random>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <sys/stat.h>


std::vector<std::string> Utils::listDirectory(const std::string& directory, bool fixPath) {
    DIR *d = opendir(directory.c_str());
    std::vector<std::string> files;
    struct dirent *dir;
    if(d) {
        while ((dir = readdir(d)) != nullptr) {
            std::string sdn(dir->d_name);
            if(sdn == "." || sdn == "..") continue;
            files.emplace_back(fixPath ? Utils::escapePath(directory + sdn) : sdn);
        }
    }
    return files;
}

std::vector<std::string> Utils::findWithPrefix(const std::string& prefix, const std::vector<std::string>& lst) {
    std::vector<std::string> ret;
    for(std::string i : lst) if(i.substr(0, prefix.size()) == prefix) ret.emplace_back(i);
    return ret;
}

bool Utils::endsWith(const std::string &data, const std::string &suffix) {
    return data.substr(data.length() - suffix.length(), data.length()) == suffix;
}

bool Utils::startsWith(const std::string &data, const std::string &prefix) {
    return data.substr(0, prefix.length()) == prefix;
}

bool Utils::isFile(std::string path) {
    return access(path.c_str(), F_OK) == 0;
}

bool Utils::isPi() {
    return Utils::isFile("/sys/firmware/devicetree/base/model");
}

std::string Utils::getUsername() {
    if(Utils::isPi()) return "pi";
    else {
        return "insane";
        /*
        char b[8];
        getlogin_r(b, 8); // todo fix?
        return std::string(b);
         */
    }
}

std::string Utils::replaceAll(std::string data, const std::string& from, const std::string& to) {
    std::string::size_type n = 0;
    while ((n = data.find(from, n)) != std::string::npos) {
        data.replace(n, from.size(), to);
        n += to.size();
    }
    return data;
}

std::string Utils::escapePath(std::string path) {
    for(const std::string& c : std::vector<std::string>{" ", "(", ")", "[", "]", "&"}) path = Utils::replaceAll(path, c, "\\" + c);
    return path;
}

std::string Utils::unescapePath(std::string path) {
    return Utils::replaceAll(std::move(path), "\\", "");
}

std::string Utils::readFile(const std::string &filename) {
    if(!Utils::isFile(filename)) return "";
    std::ifstream t(filename);
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}

std::vector<std::string> Utils::contains(const std::vector<std::string> &vec, const std::string &value, bool prefix) {
    std::vector<std::string> r;
    for(const std::string& tmp : vec) {
        if(prefix) {
            if(Utils::startsWith(tmp, value)) r.emplace_back(tmp);
        } else {
            if(Utils::endsWith(tmp, value)) r.emplace_back(tmp);
        }
    }
    return r;
}

std::vector<std::string> Utils::removeFromVector(std::vector<std::string> vec, const std::string &item) {
    vec.erase(std::remove(vec.begin(), vec.end(), item), vec.end());
    return vec;
}

std::string Utils::joinList(const std::vector<std::string>& lst, const std::string& delimiter) {
    std::string r;
    for(const std::string& t : lst) {
        r += t;
        r += delimiter;
    }
    return r.substr(0, r.size() - 1);
}

std::string Utils::buildPath(std::vector<std::string> pathItems, bool lastIsFile) {
    std::string r = "/";
    for(const std::string& i : pathItems) r += i + "/";
    if(lastIsFile) return r.substr(0, r.length() - 1);
    return r;
}

std::vector<std::string> Utils::split(const std::string& data, char delimiter) {
    std::vector<std::string> r;
    std::stringstream ss(data);
    std::string item;
    while (std::getline(ss, item, delimiter))r.emplace_back(item);
    return r;
}

// enum?
int Utils::colorStr2Base16(const std::string &color) {
    if(color == "gray") return 0x838383ff;
    else if(color == "lightGray") 0xaaaaaaff;
    else if(color == "darkGray") 0x424242ff;
    else if(color == "black") return 0x000000ff;
    else if(color == "neonGreen") return 0x43ce18ff;
    else if(color == "green") return 0x44ba1fff;
    else if(color == "darkGreen") return 0x285b17ff;
    else if(color == "red") return 0xd12121ff;
    else if(color == "darkRed") return 0x8e0202ff;
    else if(color == "orange") return 0xe5a21bff;
    else if(color == "yellow") return 0xdfe216ff;
    else if(color == "lime") return 0x8bd628ff;
    else if(color == "greenBlue") return 0x1ece76ff;
    else if(color == "lightBlue") return 0x118dd6ff;
    else if(color == "darkBlue") return 0x2b16a0ff;
    else if(color == "purple") return 0xa618e2ff;
    else if(color == "darkPurple") return 0x780aafff;
    else if(color == "pink") return 0xed0b9eff;
    else if(color == "brown") return 0x753c37ff;
    else return 0xffffffff;
}

std::string Utils::colorBase162Str(int color) {
    if(color == 0x838383ff) return "gray";
    else if(color == 0xaaaaaaff) return "lightGray";
    else if(color == 0x424242ff) return "darkGray";
    else if(color == 0x000000ff) return "black";
    else if(color == 0x43ce18ff) return "neonGreen";
    else if(color == 0x44ba1fff) return "green";
    else if(color == 0x285b17ff) return "darkGreen";
    else if(color == 0xd12121ff) return "red";
    else if(color == 0x8e0202ff) return "darkRed";
    else if(color == 0xe5a21bff) return "orange";
    else if(color == 0xdfe216ff) return "yellow";
    else if(color == 0x8bd628ff) return "lime";
    else if(color == 0x1ece76ff) return "greenBlue";
    else if(color == 0x118dd6ff) return "lightBlue";
    else if(color == 0x2b16a0ff) return "darkBlue";
    else if(color == 0xa618e2ff) return "purple";
    else if(color == 0x780aafff) return "darkPurple";
    else if(color == 0xed0b9eff) return "pink";
    else if(color == 0x753c37ff) return "brown";
    else return "white";
}

bool Utils::contains(const std::vector<std::string> &lst, const std::string &i) {
    for (const std::string &_ : lst) { if (_ == i) return true; }
    return false;
}

std::string Utils::generateString(const std::string& chars, int length) {
    std::string r;
    for(int i=0; i < length; i++) r += chars.c_str()[std::rand() % sizeof(chars.c_str()) - 1];
    return r;
}

bool Utils::contains(const std::string &data, const std::string &sub) {
    return data.find(sub) != std::string::npos;
}

void Utils::createDirectory(const std::string &path) {
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
}

bool Utils::isNumerical(const std::string &data) {
    for(const char c : data) {
        if(!std::isdigit(c)) return false;
    }
    return true;
}

float Utils::getCPUTemp() { // does not seem to work with amd ryzen 7 2700x / worked with i7
    if(Utils::isPi()){
        std::string titC = Utils::readFile("/sys/class/thermal/thermal_zone0/temp"); // celsius in thousands
        return std::stof(titC) / 1000;
    }
    return -1;
}

Processes* Utils::getRunningProcesses() {
    std::string _proc("/proc/");
    std::string _stat("/stat");
    std::vector<std::string> pids;
    for(const std::string& d : listDirectory(_proc, false)){
        if(isNumerical(d)) {pids.emplace_back(d);};
    }
    auto procs = new Processes();
    for(const std::string& p : pids){
        std::string fStat = _proc;
        fStat += p;
        fStat += _stat;
        if(isFile(fStat)){
            std::ifstream f(fStat, std::ifstream::binary);
            procs->addProcess(new Process(std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>())));
        }
    }
    return procs;
}

Process::Process() {

}

Process::Process(const std::string &stat) {
    std::vector<std::string> l = Utils::split(stat, ' ');
    pid = l[0];
    name = l[1];
    state = l[2];
    ppid = l[3];
    pgrp = l[4];
    session = l[5];
}

void Process::setName(const std::string &name) {this->name = name;}

void Process::setPgrp(const std::string &pgrp) {this->pgrp = pgrp;}

void Process::setPid(const std::string &pid) {this->pid = pid;}

void Process::setPpid(const std::string &ppid) {this->ppid = ppid;}

void Process::setSession(const std::string &session) {this->session = session;}

void Process::setState(const std::string &state) {this->state = state;}

std::string Process::getName() {return name;}

std::string Process::getPgrp() {return pgrp;}

std::string Process::getPid() {return pid;}

std::string Process::getPpid() {return ppid;}

std::string Process::getSession() {return session;}

std::string Process::getState() {return state;}

Processes::Processes() {

}

std::vector<std::string> Processes::getPids() {
    std::vector<std::string> r;
    for(Process* p : processes) r.emplace_back(p->getPid());
    return r;
}

Processes::Processes(const std::vector<Process *> &processes) {
    this->processes = processes;
}

void Processes::addProcess(Process *process) {
    if(!Utils::contains(getPids(), process->getPid())) processes.emplace_back(process);
}

bool Processes::isRunning(const std::string &name) {
    for(Process* p : processes){
        if(p->getName() == name) return (p->getState() == "R" || p->getState() == "S");
    }
    return false;
}

std::vector<Process*> Processes::getProcesses() {return processes;}

std::string Utils::getCurrentTime() {
    time_t c = time(nullptr);
    char b[20];
    strftime(b, 20, "%d.%m.%Y %H:%M:%S", localtime(&c));
    return std::string(b);
}

double Utils::getDirectorySize(const std::string &path) {
    struct statvfs dd;
    statvfs(path.c_str(), &dd);
    double r = dd.f_favail * dd.f_bsize;
    std::cout << path << ": " << r << std::endl;
    return r;
}

double Utils::getFileSize(const std::string &path) {
    std::ifstream i(path, std::ios::binary|std::ios::ate);
    double r = i.tellg();
    std::cout << path << ": " << r << std::endl;
    return r;
}

bool Utils::isDirectory(const std::string& path) {
    struct stat i;
    stat(path.c_str(), &i);
    return S_ISDIR(i.st_mode);
}