//
// Created by nbdy on 10.10.21.
//

#include "carpi_config.h"
#include "CMM.h"


struct Configuration {
  const char* m_sConfigurationPath = nullptr;

  const char* m_sModuleDirectory = nullptr;

  static Configuration parse(int argc, char** argv) {
    Configuration cfg {};
    for(uint32_t i = 0; i < argc; i++) {
      if(!strcmp(argv[i], "-md") || !strcmp(argv[i], "--module-directory")) {
        cfg.m_sModuleDirectory = argv[i + 1];
      }
    }
    return cfg;
  }

  [[nodiscard]] bool isOk() const {
    return m_sConfigurationPath != nullptr ||
           m_sModuleDirectory != nullptr;
  }
};


int main(int argc, char** argv) {
  bool bRun = true;

  auto cfg = Configuration::parse(argc, argv);

  cfg.m_sModuleDirectory = "modules/";

  if(!cfg.isOk()) {
    return ERROR_CONFIGURATION;
  }

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APPLICATION_NAME);
  SetTargetFPS(60);

  int moduleListViewSelection = -1;
  int moduleListViewScrollIndex = 0;
  int moduleListViewPreviousSelection = moduleListViewSelection;

  CMM moduleManager(cfg.m_sModuleDirectory);

  std::function<void()> fCheckModuleSelection = [&moduleManager, &moduleListViewSelection, &moduleListViewScrollIndex, &moduleListViewPreviousSelection]{
    static ModuleWrapper<IModule>* drawModule = nullptr;

    moduleListViewPreviousSelection = moduleListViewSelection;
    moduleListViewSelection = GuiListView(Rectangle {2, 2, MODULE_SCROLLER_WIDTH, SCREEN_HEIGHT - 4},
                                          moduleManager.getModuleNamesDelimited(";").c_str(), &moduleListViewScrollIndex, moduleListViewSelection);
    if(moduleListViewSelection != moduleListViewPreviousSelection) {
      if(!moduleManager.getModuleByIndex(moduleListViewSelection, drawModule)) {
        WLOGA("Could not find module at index %i", moduleListViewSelection);
      }
    }

    if(moduleListViewSelection == 0)
    if(drawModule != nullptr) {
      drawModule->getModule()->draw(MODULE_SCROLLER_WIDTH, 2);
    }
  };

  while(bRun) {
    bRun = !WindowShouldClose();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    fCheckModuleSelection();

    EndDrawing();
  }

  CloseWindow();

  return ERROR_NONE;
}
