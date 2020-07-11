//
// Created by insane on 02.02.19.
//

#ifndef CARPI_UTILS_H
#define CARPI_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <sys/statvfs.h>

// todo maybe use fscanf
// http://man7.org/linux/man-pages/man5/proc.5.html
class Process {
private:
    std::string name;
    std::string pid;
    std::string state;
    std::string ppid;
    std::string pgrp;
    std::string session;

public:
    Process();
    explicit Process(const std::string& stat);

    std::string getName();
    std::string getPid();
    std::string getState();
    std::string getPpid();
    std::string getPgrp();
    std::string getSession();

    void setName(const std::string& name);
    void setPid(const std::string& pid);
    void setState(const std::string& state);
    void setPpid(const std::string& ppid);
    void setPgrp(const std::string& pgrp);
    void setSession(const std::string& session);
};

class Processes {
private:
    std::vector<Process*> processes;

public:
    Processes();
    explicit Processes(const std::vector<Process*>& processes);

    std::vector<std::string> getPids();
    std::vector<Process*> getProcesses();
    void addProcess(Process* process);
    bool isRunning(const std::string& name);
};

class Utils {
public:
    static std::string generateString(const std::string& chars, int length);

    static bool contains(const std::vector<std::string> &lst, const std::string &i);
    static bool contains(const std::string& data, const std::string& sub);
    static std::vector<std::string> contains(const std::vector<std::string>& vec, const std::string& value, bool prefix);

    static std::string joinList(const std::vector<std::string>& lst, const std::string& delimiter);

    static std::vector<std::string> split(const std::string& data, char delimiter);

    static std::string buildPath(std::vector<std::string> pathItems, bool lastIsFile);

    static std::vector<std::string> listDirectory(const std::string& directory, bool fixPath);

    static std::vector<std::string> findWithPrefix(const std::string& prefix, const std::vector<std::string>& lst);

    static bool startsWith(const std::string& data, const std::string& prefix);
    static bool endsWith(const std::string& data, const std::string& suffix);

    static std::vector<std::string> removeFromVector(std::vector<std::string> vec, const std::string& item);

    static bool isPi();

    static std::string getUsername();

    static std::string replaceAll(std::string data, const std::string& from, const std::string& to);

    static std::string escapePath(std::string path);

    static std::string readFile(const std::string& filename);

    static double getDirectorySize(const std::string& path);

    static double getFileSize(const std::string& path);

    static std::string unescapePath(std::string path);

    static int colorStr2Base16(const std::string& color);
    static std::string colorBase162Str(int color);

    static void createDirectory(const std::string& path);

    static bool isDirectory(const std::string& path);
    static bool isFile(std::string path);
    static bool isNumerical(const std::string& data);

    static Processes* getRunningProcesses();
    static float getCPUTemp();
    static std::string getCurrentTime();
};


#endif //CARPI_UTILS_H
