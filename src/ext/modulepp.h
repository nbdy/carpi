/*

MIT License

    Copyright (c) 2021 Pascal Eberlein

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                                                              copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.

            */

#ifndef LIBMODULEPP_MODULEPP_H
#define LIBMODULEPP_MODULEPP_H

#define USE_OHLOG

#ifdef USE_OHLOG
#include "ohlog.h"
#endif

// #define ENABLE_DRAW_FUNCTION
// #define ENABLE_SHARED_DATA

#ifdef ENABLE_DRAW_FUNCTION
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#endif

#ifdef ENABLE_SHARED_DATA
#include "json.hpp"
#endif

#include <any>
#include <atomic>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <chrono>
#include <fcntl.h>
#include <dlfcn.h>
#include <filesystem>
#include <sstream>
#include <condition_variable>
#include <shared_mutex>

#define F_CREATE(T) extern "C" T* create() {return new T;}

using Path = std::filesystem::path;
using SharedLock = std::shared_lock<std::shared_mutex>;
using UniqueLock = std::unique_lock<std::mutex>;
using LockGuard = std::lock_guard<std::mutex>;
using Clock = std::chrono::high_resolution_clock;
using Milliseconds = std::chrono::milliseconds;
using Nanoseconds = std::chrono::nanoseconds;

#define TIMESTAMP_MS std::chrono::duration_cast<Milliseconds>(Clock::now().time_since_epoch()).count()
#define TIMESTAMP_NS std::chrono::duration_cast<Nanoseconds>(Clock::now().time_since_epoch()).count()

namespace modulepp {

class ModuleVersion {
  uint32_t m_u32Major = 0U;
  uint32_t m_u32Minor = 1U;
  uint32_t m_u32Patch = 0U;

public:
  ModuleVersion() = default;
  ModuleVersion(const ModuleVersion &other) {
    m_u32Major = other.m_u32Major;
    m_u32Minor = other.m_u32Minor;
    m_u32Patch = other.m_u32Patch;
  }
  ModuleVersion(uint32_t i_u32Major, uint32_t i_u32Minor, uint32_t i_u32Patch)
      : m_u32Major(i_u32Major), m_u32Minor(i_u32Minor), m_u32Patch(i_u32Patch) {
  }

  [[nodiscard]] std::string toString() const {
    std::stringstream r;
    r << std::to_string(m_u32Major) << "." << std::to_string(m_u32Minor) << "."
      << std::to_string(m_u32Patch);
    return r.str();
  }
};

class ModuleInformation {
  ModuleVersion m_Version{0U, 1U, 0U};
  std::string m_sName;

public:
  ModuleInformation() = default;
  explicit ModuleInformation(std::string i_sName)
      : m_sName(std::move(i_sName)){};
  ModuleInformation(std::string i_sName, const ModuleVersion &i_Version)
      : m_sName(std::move(i_sName)), m_Version(i_Version){};

  [[nodiscard]] std::string toString() const {
    std::stringstream r;
    r << m_sName << " " << m_Version.toString();
    return r.str();
  };

  [[nodiscard]] ModuleVersion getVersion() const { return m_Version; };

  [[nodiscard]] std::string getName() const { return m_sName; }
};

class ModuleDependency : public ModuleInformation {
  bool m_bOptional = false;

public:
  explicit ModuleDependency(const std::string &i_sName)
      : ModuleInformation(i_sName){};
  explicit ModuleDependency(const ModuleInformation &i_Information)
      : ModuleInformation(i_Information){};
  ModuleDependency(const std::string &i_sName, bool i_bOptional)
      : ModuleInformation(i_sName), m_bOptional(i_bOptional){};
  ModuleDependency(const ModuleInformation &i_Information, bool i_bOptional)
      : ModuleInformation(i_Information), m_bOptional(i_bOptional){};

  [[nodiscard]] bool isOptional() const { return m_bOptional; }
};

class IModule {
private:
  enum Error { OK = 0, NO_EXIST, WRONG_FILE };

  uint32_t m_u32CycleTime_ms = 500U;
  std::atomic_bool m_bRun = {true};
  std::atomic_bool m_bEnable = {false};
  std::atomic_bool m_bWorkTooExpensive = {false};
  Error m_Error = OK;
  std::string m_sError;
  std::thread m_Thread;
  std::mutex m_Mutex;
  std::condition_variable m_Condition;
  ModuleInformation m_Information;
  uint64_t m_u64FunctionStartTimestamp = 0;
  uint64_t m_u64FunctionEndTimestamp = 0;
  uint64_t m_u64FunctionTime = 0;
  uint32_t m_u32ModifiedInterval = 0;
  std::vector<ModuleDependency> m_Dependencies;
#ifdef ENABLE_SHARED_DATA
  nlohmann::json m_SharedData;
  std::mutex m_SharedDataMutex;
#endif

protected:
  std::map<std::string, IModule *> m_DependencyMap;

public:
  template <typename T>
  static T *load(const Path &i_FilePath, const char *i_sCreateFunction) {
    typedef T *create_t();
    Error error = OK;
    const char *errorString = nullptr;
    void *handle = nullptr;
    T *module = nullptr;

    if (!std::filesystem::exists(i_FilePath)) {
      error = NO_EXIST;
    }

    if (error == OK && i_FilePath.has_extension() &&
        i_FilePath.extension() == ".so") {
      (void)dlerror(); // clear errors
      handle = dlopen(i_FilePath.c_str(), RTLD_LAZY);
      module = ((create_t *)dlsym(handle, i_sCreateFunction))();
      errorString = dlerror();
      if (errorString != nullptr) {
        ELOGA("Could not load module: %s", i_FilePath.c_str());
      }
    } else {
      error = WRONG_FILE;
    }

    module->setError(error);
    module->setErrorString(errorString);
    module->setHandle(handle);
  }

  void _setName() {
#ifdef USE_OHLOG
    DLOGA("Setting thread name: %s", m_Information.toString().c_str());
#endif
    pthread_setname_np(m_Thread.native_handle(),
                       m_Information.toString().c_str());
  }

  void _setPriority() {
#ifdef USE_OHLOG
    DLOGA("Setting thread priority: %s | Priority: %i",
          m_Information.toString().c_str(), 50);
#endif
    pthread_setschedprio(m_Thread.native_handle(), 50);
  }

  IModule() : m_Thread([this] { run(); }), m_Information() {
    _setName();
    _setPriority();
  };
  explicit IModule(ModuleInformation i_Information)
      : m_Thread([this] { run(); }), m_Information(std::move(i_Information)) {
    _setName();
    _setPriority();
  };
  IModule(ModuleInformation i_Information,
          std::vector<ModuleDependency> i_Dependencies)
      : m_Thread([this] { run(); }), m_Information(std::move(i_Information)),
        m_Dependencies(std::move(i_Dependencies)) {
    _setName();
    _setPriority();
  };

  ~IModule() {
    kill();
    join();
  }

  bool start() {
    if (m_bEnable) {
      return false;
    }
    m_bRun = true;
    m_bEnable = true;
    m_Condition.notify_one();
    return true;
  };

  void stop() {
    m_bEnable = false;
    m_Condition.notify_one();
  };

  void kill() {
    m_bRun = false;
    m_bEnable = false;
    m_Condition.notify_one();
  }

  bool join() {
    bool r = false;
    if (m_Thread.joinable()) {
      m_Thread.join();
      r = true;
    }
    return r;
  };

  void _waitUntilEnabled() {
    UniqueLock ul(m_Mutex);
    m_Condition.wait(
        ul, [this] { return this->m_bEnable.load() || !this->m_bRun.load(); });
  };

  void _timeWork() {
    m_u64FunctionStartTimestamp = TIMESTAMP_MS;
    work();
    m_u64FunctionEndTimestamp = TIMESTAMP_MS;
    m_u64FunctionTime = m_u64FunctionEndTimestamp - m_u64FunctionStartTimestamp;
    if (m_u64FunctionTime > m_u32CycleTime_ms) {
      m_bWorkTooExpensive = true;
      m_u32ModifiedInterval = 0;
    } else {
      m_bWorkTooExpensive = false;
      m_u32ModifiedInterval = m_u32CycleTime_ms - m_u64FunctionTime;
    }
  };

  void run() {
    CATCHMN(_waitUntilEnabled, m_Information.toString().c_str(),
            "WaitUntilEnabled");
    CATCHMN(onStart, m_Information.toString().c_str(), "OnStart");
    while (m_bRun) {
      _waitUntilEnabled();

      while (m_bEnable) {
        _timeWork();
        std::this_thread::sleep_for(Milliseconds(m_u32CycleTime_ms));
      }
    }
    CATCHMN(onStop, m_Information.toString().c_str(), "OnStop");
  };

  virtual void work(){};
  virtual void onStart(){};
  virtual void onStop(){};

#ifdef ENABLE_DRAW_FUNCTION
  virtual void draw(float i_fX, float i_fY){};
  virtual void drawInformation(float i_fX, float i_fY) {
    GuiLabel(Rectangle{i_fX, i_fY, 64, 16}, "Information");
    i_fX += 8;
    GuiLabel(Rectangle{i_fX, i_fY + 16, 64, 16},
             ("Version: " + m_Information.getVersion().toString()).c_str());
    GuiLabel(
        Rectangle{i_fX, i_fY + 32, 64, 16},
        ("Dependencies: " + std::to_string(m_Dependencies.size())).c_str());
    GuiLabel(Rectangle{i_fX, i_fY + 48, 64, 16},
             ("Error: " + m_sError).c_str());
    GuiLabel(Rectangle{i_fX, i_fY + 64, 64, 16},
             ("Work function time (ms): " + std::to_string(m_u64FunctionTime))
                 .c_str());
    GuiLabel(
        Rectangle{i_fX, i_fY + 80, 64, 16},
        ("Modified cycle time (ms): " + std::to_string(m_u32ModifiedInterval))
            .c_str());
    GuiLabel(Rectangle{i_fX, i_fY + 96, 64, 16},
             ("Path: " + getFilePath().string()).c_str());
  };
  virtual void drawSettings(float i_fX, float i_fY) {
    GuiLabel(Rectangle{i_fX, i_fY, 64, 16}, "Settings");
    m_bEnable = GuiCheckBox(Rectangle{i_fX + 8, i_fY + 16, 16, 16}, "Enable",
                            m_bEnable);
    GuiValueBox(Rectangle{i_fX + 64, i_fY + 36, 256, 16}, "Cycle time",
                (int *)&m_u32CycleTime_ms, 10, 10000, true);
  };
  void drawDependencies(float i_fX, float i_fY, float i_fWidth = 128,
                        float i_fHeight = 256) {
    GuiLabel(Rectangle{i_fX, i_fY, i_fWidth, 16}, "Dependencies");
    auto x = getModuleDependenciesDelimited();
    if (!x.empty()) {
      GuiListView(Rectangle{i_fX, i_fY + 16, i_fWidth, i_fHeight}, x.c_str(),
                  nullptr, -1);
    }
  };
#endif

#ifdef ENABLE_SHARED_DATA
  template <class T>
  void setSharedData(T *obj, void (T::*function)(nlohmann::json &)) {
    LockGuard lg(m_SharedDataMutex);
    std::bind(function, obj, std::placeholders::_1)(m_SharedData);
  };

  nlohmann::json getSharedData() {
    LockGuard lg(m_SharedDataMutex);
    return m_SharedData;
  }
#endif

  [[nodiscard]] bool hasError() const { return !m_sError.empty(); };

  [[nodiscard]] std::string getError() const { return m_sError; };

  [[nodiscard]] bool isRunning() const { return m_bRun; };

  [[nodiscard]] bool isEnabled() const { return m_bEnable; }

  [[nodiscard]] uint32_t getCycleTime() const { return m_u32CycleTime_ms; };

  void setCycleTime(uint32_t i_u32CycleTime) {
    m_u32CycleTime_ms = i_u32CycleTime;
  };

  [[nodiscard]] ModuleInformation getInformation() const {
    return m_Information;
  }

  std::vector<ModuleDependency> getModuleDependencies() {
    return m_Dependencies;
  }

  static std::string getModuleInformationVector2DelimitedString(
      const std::vector<ModuleDependency> &i_Modules,
      const std::string &i_sDelimiter = ";") {
    std::stringstream r;
    std::for_each(i_Modules.begin(), i_Modules.end(),
                  [&r](const ModuleDependency &i_Dependency) {
                    r << i_Dependency.getName() << ";";
                  });
    auto x = r.str();
    return x.substr(0, x.size() - 1);
  }

  std::string
  getModuleDependenciesDelimited(const std::string &i_sDelimiter = ";") {
    return getModuleInformationVector2DelimitedString(m_Dependencies,
                                                      i_sDelimiter);
  }

  bool hasDependencies() { return !m_Dependencies.empty(); }

  static std::filesystem::path getFilePath() {
    Dl_info info{};
    dladdr((void *)getFilePath, &info);
    return info.dli_fname;
  }

  bool isDrawable() {
#ifdef ENABLE_DRAW_FUNCTION
    return true;
#else
    return false;
#endif
  }
};

template <typename ModuleType> class ModuleWrapper {
  typedef ModuleType *create_t();

  enum Error { OK = 0, NO_EXIST, WRONG_FILE };

  Path m_FilePath;
  const char *m_sCreateFunction = nullptr;

  void *m_pHandle = nullptr;
  ModuleType *m_pModule = nullptr;

  Error m_Error = OK;
  const char *m_sError = nullptr;

  bool m_bSystemModule = false;

  void load() {
#ifdef OHLOG
    DLOGA("Trying to load: %s", m_FilePath.c_str());
#endif

    if (!std::filesystem::exists(m_FilePath)) {
      m_Error = NO_EXIST;
    }

    if (m_FilePath.has_extension() && m_FilePath.extension() == ".so") {
      (void)dlerror(); // clear errors
      m_sError = nullptr;
      m_pHandle = dlopen(m_FilePath.c_str(), RTLD_LAZY);
      m_pModule = ((create_t *)dlsym(m_pHandle, m_sCreateFunction))();
      m_sError = dlerror();
      if (m_sError != nullptr) {
        ELOGA("Could not load module: %s", m_FilePath.c_str());
      }
    } else {
      m_Error = WRONG_FILE;
    }
  }

  void fromModule() {
    Dl_info info{};
    if (dladdr(m_pModule, &info) != 0) {
      if (info.dli_fname != nullptr) {
        m_FilePath = info.dli_fname;
      }
      m_pHandle = info.dli_fbase;
    }
  }

public:
  ModuleWrapper() = default;

  explicit ModuleWrapper(IModule *i_pModule)
      : m_pModule(i_pModule), m_bSystemModule(true) {
#ifdef USE_OHLOG
    DLOGA("%s - Creating system module",
          i_pModule->getInformation().toString().c_str());
#endif
    fromModule();
  }

  explicit ModuleWrapper(const char *i_sFilePath,
                         const char *i_sCreateFunction = "create",
                         bool i_bAutoLoad = true)
      : m_FilePath(i_sFilePath), m_sCreateFunction(i_sCreateFunction) {
#ifdef USE_OHLOG
    DLOGA("Creating normal module from: %s", i_sFilePath);
#endif
    if (i_bAutoLoad) {
      load();
    }
  }

  ~ModuleWrapper() {
    if (!m_bSystemModule) {
#ifdef USE_OHLOG
      DLOG("Destructing");
#endif
      delete m_pModule;
      if (m_pHandle != nullptr) {
        dlclose(m_pHandle);
      }
    }
#ifdef USE_OHLOG
    else {
      DLOG("System module!");
    }
#endif
  }

  [[nodiscard]] ModuleType *getModule() const { return m_pModule; }

  [[nodiscard]] std::filesystem::path getFilePath() const { return m_FilePath; }
};

class ModuleLoader {
public:
  template <typename ModuleType>
  static std::vector<ModuleWrapper<ModuleType> *>
  loadDirectory(const Path &path) {
    std::vector<ModuleWrapper<ModuleType> *> r;
    for (const auto &e : std::filesystem::directory_iterator(path)) {
      r.push_back(new ModuleWrapper<ModuleType>(e.path().c_str()));
    }
    return r;
  }

  template <typename ModuleType>
  static std::vector<ModuleWrapper<ModuleType> *>
  loadDirectoryRecursive(const Path &path) {
#ifdef USE_OHLOG
    DLOGA("Loading recursively: %s", path.c_str());
#endif
    std::vector<ModuleWrapper<ModuleType> *> r;
    for (const auto &e : std::filesystem::recursive_directory_iterator(path)) {
      if (e.path().has_extension() && e.path().extension() == ".so") {
        r.push_back(new ModuleWrapper<ModuleType>(e.path().c_str()));
      }
    }
    return r;
  }

  template <typename ModuleType>
  static std::vector<ModuleWrapper<ModuleType> *>
  loadDirectory(const Path &path, bool recursive) {
#ifdef USE_OHLOG
    DLOGA("Loading non-recursively: %s", path.c_str());
#endif
    std::vector<ModuleWrapper<ModuleType> *> r;
    if (recursive) {
      r = loadDirectoryRecursive<ModuleType>(path);
    } else {
      r = loadDirectory<ModuleType>(path);
    }
    return r;
  }
};

class ModuleManager {
  std::filesystem::path m_ModuleDirectoryPath;
  std::mutex m_ModulesMutex;
  std::vector<ModuleWrapper<IModule> *> m_Modules;

#ifdef ENABLE_DRAW_FUNCTION
  std::atomic_uint32_t m_u32VisibleModule = 0;
#endif

  bool _resolveModuleDependencies(ModuleWrapper<IModule> *i_Module) {
    bool r = false;
    auto *m = i_Module->getModule();
    if (m == nullptr) {
      ELOG("Something went really wrong.");
    }

    auto moduleDependencies = m->getModuleDependencies();

    if (!moduleDependencies.empty()) {
      ModuleWrapper<IModule> *dep = nullptr;
      for (const auto &dependency : moduleDependencies) {
#ifdef USE_OHLOG
        DLOGA("Searching for module '%s'", dependency.toString().c_str());
#endif
        if (!getModuleByInformation(dependency, dep, false)) {

        }
#ifdef USE_OHLOG
        else {
          WLOGA("Failed to find dependency '%s' for module '%s",
                dependency.toString().c_str(),
                m->getInformation().toString().c_str());
        }
#endif
      }
    }
#ifdef USE_OHLOG
    else {
      DLOG("This module has no dependencies");
    }
#endif

    return r;
  }

  void _resolveModuleDependencies() {
#ifdef USE_OHLOG
    DLOG("Resolving module dependencies");
#endif
    for (const auto &v : m_Modules) {
      _resolveModuleDependencies(v);
    }
  }

protected:
  void init(bool i_bRecursive) {
#ifdef USE_OHLOG
    DLOG("Initializing");
#endif
    std::vector<ModuleWrapper<IModule> *> tmp;
    LockGuard lg(m_ModulesMutex);
    if (i_bRecursive) {
      m_Modules =
          ModuleLoader::loadDirectoryRecursive<IModule>(m_ModuleDirectoryPath);
    } else {
      m_Modules = ModuleLoader::loadDirectory<IModule>(m_ModuleDirectoryPath);
    }
#ifdef USE_OHLOG
    DLOGA("Loaded %i modules", m_Modules.size());
#endif
    _resolveModuleDependencies();
  }

public:
  explicit ModuleManager(std::filesystem::path i_Path, bool i_bInit = true)
      : m_ModuleDirectoryPath(std::move(i_Path)) {
    if (i_bInit) {
      init(false);
    }
  }

  ModuleManager(std::filesystem::path i_Path, bool i_bRecursive,
                bool i_bInit = true)
      : m_ModuleDirectoryPath(std::move(i_Path)) {
    if (i_bInit) {
      init(i_bRecursive);
    }
  }

  ~ModuleManager() {
#ifdef USE_OHLOG
    DLOG("");
#endif
  }

  bool destroyModule(uint32_t i_u32Index) {
    bool r = false;
    LockGuard lg(m_ModulesMutex);
    if (m_Modules.size() >= i_u32Index) {
      if (m_Modules[i_u32Index] != nullptr) {
        delete m_Modules[i_u32Index];
        m_Modules[i_u32Index] = nullptr;
      }
      r = true;
      m_Modules.erase(
          std::remove(std::begin(m_Modules), std::end(m_Modules), nullptr),
          std::end(m_Modules));
    }
    return r;
  }

  void start() {
    LockGuard lg(m_ModulesMutex);
    for (const auto &m : m_Modules) {
      m->getModule()->start();
    }
  }

  void stop() {
    LockGuard lg(m_ModulesMutex);
    for (const auto &m : m_Modules) {
      m->getModule()->stop();
    }
  }

  std::vector<std::string> getModuleNames() {
    std::vector<std::string> r;
    LockGuard lg(m_ModulesMutex);
    for (const auto &m : m_Modules) {
      r.push_back(m->getModule()->getInformation().getName());
    }
    return r;
  }

  static std::string getModuleNamesDelimited(
      const std::string &i_sDelimiter,
      const std::vector<ModuleWrapper<IModule> *> &i_Modules) {
    std::stringstream r;
    for (const auto &m : i_Modules) {
      r << m->getModule()->getInformation().getName() << i_sDelimiter;
    }
    return r.str().substr(0, r.str().size() - 1);
  }

  std::string getModuleNamesDelimited(const std::string &i_sDelimiter) {
    LockGuard lg(m_ModulesMutex);
    return getModuleNamesDelimited(i_sDelimiter, m_Modules);
  }

  uint32_t getModuleCount() {
    LockGuard lg(m_ModulesMutex);
    return m_Modules.size();
  }

  bool getModuleByInformation(const ModuleInformation &i_Information,
                              ModuleWrapper<IModule> *&o_Module,
                              bool i_bLock = true) {
    bool r = false;
    if (i_bLock) {
      LockGuard lg(m_ModulesMutex);
    }
    for (const auto &m : m_Modules) {
      if (m->getModule()->getInformation().toString() ==
          i_Information.toString()) {
        o_Module = m;
        r = true;
        break;
      }
    }
    return r;
  }

  bool getModuleByName(const std::string &i_sName,
                       ModuleWrapper<IModule> *&o_Module) {
    bool r = false;
    LockGuard lg(m_ModulesMutex);
    for (const auto &m : m_Modules) {
      if (m->getModule()->getInformation().getName() == i_sName) {
        o_Module = m;
        r = true;
      }
    }
    return r;
  }

  bool getModuleByIndex(uint32_t i_u32Index,
                        ModuleWrapper<IModule> *&o_Module) {
    LockGuard lg(m_ModulesMutex);
    bool r = false;
    if (i_u32Index <= m_Modules.size()) {
      DLOGA("Found module %s at index %i",
            m_Modules[i_u32Index]
                ->getModule()
                ->getInformation()
                .toString()
                .c_str(),
            i_u32Index);
      o_Module = m_Modules[i_u32Index];
      r = true;
    }
    return r;
  }

  bool addModule(IModule *i_pModule) {
#ifdef USE_OHLOG
    DLOGA("Adding '%s'", i_pModule->getFilePath().c_str());
#endif
    bool r = false;
    bool found = false;
    LockGuard lg(m_ModulesMutex);
    for (const auto &module : m_Modules) {
      if (module->getModule()->getInformation().toString() ==
          i_pModule->getInformation().toString()) {
        found = true;
      }
    }
    if (!found) {
#ifdef USE_OHLOG
      DLOGA("%s is not loaded yet, adding it",
            i_pModule->getInformation().toString().c_str());
#endif
      m_Modules.emplace_back();
      _resolveModuleDependencies(m_Modules[m_Modules.size() - 1]);
      r = true;
    }
#ifdef USE_OHLOG
    DLOGA("Adding module '%s': %s",
          i_pModule->getInformation().toString().c_str(),
          r ? "success" : "failed");
#endif
    return r;
  }

  bool addModule(ModuleWrapper<IModule> *i_Module) {
#ifdef USE_OHLOG
    DLOGA("Adding '%s'", i_Module->getModule()->getFilePath().c_str());
#endif
    bool r = false;
    bool found = false;
    LockGuard lg(m_ModulesMutex);
    for (const auto &module : m_Modules) {
      if (module->getModule()->getInformation().toString() ==
          i_Module->getModule()->getInformation().toString()) {
        found = true;
      }
    }
    if (!found) {
#ifdef USE_OHLOG
      DLOGA("%s is not loaded yet, adding it",
            i_Module->getModule()->getInformation().toString().c_str());
#endif
      m_Modules.emplace_back(i_Module);
      _resolveModuleDependencies(i_Module);
      r = true;
    }
#ifdef USE_OHLOG
    DLOGA("Adding module '%s': %s",
          i_Module->getModule()->getInformation().toString().c_str(),
          r ? "success" : "failed");
#endif
    return r;
  }

  std::vector<ModuleWrapper<IModule> *>
  getLoadableModules(bool i_bRecursive = false) {
    auto modules = ModuleLoader::loadDirectory<IModule>(m_ModuleDirectoryPath,
                                                        i_bRecursive);
    std::vector<ModuleWrapper<IModule> *> unloadedModules;
    bool isModuleAlreadyLoaded = false;
    LockGuard lg(m_ModulesMutex);
    for (const auto &m : modules) {
      isModuleAlreadyLoaded = false;
      for (const auto &lm : m_Modules) {
        if (m->getModule()->getInformation().toString() ==
            lm->getModule()->getInformation().toString()) {
          isModuleAlreadyLoaded = true;
          break;
        }
      }
      if (!isModuleAlreadyLoaded) {
        unloadedModules.push_back(m);
      }
    }
    return unloadedModules;
  }

  std::filesystem::path getModulesDirectory() { return m_ModuleDirectoryPath; }

#ifdef ENABLE_DRAW_FUNCTION
  ModuleWrapper<IModule> *getVisibleModule() {
    LockGuard lg(m_ModulesMutex);
    return m_Modules[m_u32VisibleModule];
  }

  void setModuleVisible(uint32_t i_u32ModuleIndex) {
    m_u32VisibleModule = i_u32ModuleIndex;
  }
#endif
};

}

#endif //LIBMODULEPP_MODULEPP_H
