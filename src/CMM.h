//
// Created by nbdy on 21.11.21.
//

#ifndef CARPI_SRC_CMM_H_
#define CARPI_SRC_CMM_H_

#include <filesystem>

#define ENABLE_DRAW_FUNCTION
#include "modulepp.h"

constexpr uint32_t MODULE_SETTING_OFFSET = MODULE_CONTENT_OFFSET + MODULE_SCROLLER_WIDTH + 8;

using namespace modulepp;

class CMM : public ModuleManager, public IModule {
  int m_iListSelection = -1;
  int m_iPreviousListSelection = -1;
  int m_iListScrollIndex = 0;

  int m_iLoadableListSelection = -1;
  int m_iPreviousLoadableListSelection = -1;
  int m_iLoadableListScrollIndex = 0;
  std::string m_sLoadableListString;

  int m_iLoadedListSelection = -1;
  int m_iPreviousLoadedListSelection = -1;
  int m_iLoadedListScrollIndex = 0;
  std::string m_sLoadedListString;

  ModuleWrapper<IModule> *m_pCurrentModule = nullptr;
  std::vector<ModuleWrapper<IModule>*> m_LoadableModules;

public:
  explicit CMM(const std::filesystem::path& i_ModulePath) : ModuleManager(i_ModulePath, true, false), IModule(ModuleInformation {"ModuleManager"}) {
    if(!addModule(new ModuleWrapper<IModule>(this))){
#ifdef USE_OHLOG
      DLOGA("Could not add module: %s", getInformation().toString().c_str());
#endif
    }
    init(true);
#ifdef USE_OHLOG
    DLOGA("Loaded %i modules", getModuleCount());
#endif
    m_LoadableModules = getLoadableModules(true);
    m_sLoadableListString = getModuleMap2DelimitedString(m_LoadableModules);
    m_sLoadedListString = getModuleNamesDelimited(";");
  }

  ~CMM() {
    DLOG("Unloading all modules");
    auto cnt = getModuleCount();
    for(uint32_t idx = 0; idx < cnt; idx++) {
      destroyModule(idx);
    }
  }

  void work() override {

  }

  static std::string getModuleMap2DelimitedString(const std::vector<ModuleWrapper<IModule>*>& i_vModules) {
    std::stringstream r;
    for(const auto& m : i_vModules) {
      r << m->getModule()->getInformation().getName() << ";";
    }
    return r.str().substr(0, r.str().size() - 1);
  }

  void updateModuleListViews() {
    m_LoadableModules = getLoadableModules(true);
    m_sLoadableListString = getModuleMap2DelimitedString(m_LoadableModules);
    m_sLoadedListString = getModuleNamesDelimited(";");
  }

  void drawModuleLoader(float i_fX, float i_fY) {
    GuiLabel(Rectangle{i_fX, i_fY, 64, 16}, "Loadable modules");
    GuiLabel(Rectangle{i_fX + 288, i_fY, 64, 16}, "Loaded modules");

    if(GuiButton(Rectangle{i_fX + 128, i_fY + 16, 160, 32}, "Refresh")) {
      updateModuleListViews();
    }

    if(!m_sLoadableListString.empty()) {
      m_iPreviousLoadableListSelection = m_iLoadableListSelection;
      m_iLoadableListSelection = GuiListView(Rectangle{i_fX, i_fY + 16, 128, 256}, m_sLoadableListString.c_str(), &m_iLoadableListScrollIndex, m_iLoadableListSelection);
      if(m_iLoadableListSelection != m_iPreviousLoadableListSelection) {
        m_iLoadedListSelection = -1;
      }
    }
    if(!m_sLoadedListString.empty()) {
      m_iPreviousLoadedListSelection = m_iLoadedListSelection;
      m_iLoadedListSelection = GuiListView(Rectangle{i_fX + 288, i_fY + 16, 128, 256}, m_sLoadedListString.c_str(), &m_iLoadedListScrollIndex, m_iLoadedListSelection);
      if(m_iLoadedListSelection != m_iPreviousLoadedListSelection) {
        m_iLoadableListSelection = -1;
      }
    }

    if(m_iLoadableListSelection != -1) {
      if(GuiButton(Rectangle{i_fX + 128, i_fY + 48, 160, 32}, "Load")) {
        addModule(m_LoadableModules[m_iLoadableListSelection]);
        updateModuleListViews();
      }
    }

    if(m_iLoadedListSelection != -1) {
      if(GuiButton(Rectangle {i_fX + 128, i_fY + 48, 160, 32}, "Unload")) {
        if(destroyModule(m_iLoadedListSelection)) {
          updateModuleListViews();
        } else {
          WLOGA("Could not find module at index %i", m_iLoadedListSelection);
        }
      }
    }
  }

  void draw(float i_fX, float i_fY) override {
    static auto xOffset = i_fX + MODULE_SCROLLER_WIDTH + 16;

    if(m_pCurrentModule != nullptr) {
      drawInformation(xOffset, i_fY);
      drawSettings(xOffset, i_fY + 112);
      if(hasDependencies()) {
        drawDependencies(xOffset, i_fY + 176);
      }
      if(m_pCurrentModule->getModule()->getInformation().getName() == "ModuleManager") {
        drawModuleLoader(xOffset, i_fY + 256);
      }
    }

    m_iPreviousListSelection = m_iListSelection;
    m_iListSelection = GuiListView(Rectangle {MODULE_CONTENT_OFFSET, i_fY, MODULE_SCROLLER_WIDTH, SCREEN_HEIGHT - i_fY - 2},
                                   getModuleNamesDelimited(";").c_str(), &m_iListScrollIndex, m_iListSelection);
    if(m_iListSelection != m_iPreviousListSelection) {
      if(!getModuleByIndex(m_iListSelection, m_pCurrentModule)) {
        WLOGA("Could not find module at index %i", m_iListSelection);
      }
    }
  }
};

#endif // CARPI_SRC_CMM_H_
