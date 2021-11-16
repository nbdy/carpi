//
// Created by nbdy on 10.10.21.
//

#include <sstream>

#include "ohlog.h"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "ext/raygui.h"

#include "carpi_config.h"
#include "ext/modulepp.h"

#define RECT (Rectangle)


class Modules {
private:
  std::vector<IModule*> m_Modules;

public:
  Modules() {
    reload();
  }

  void killall() {
    DLOG("Killing all modules");
    if(!m_Modules.empty()) {
      std::for_each(m_Modules.begin(), m_Modules.end(), [](IModule* module) {
        module->kill();
        module->join();
        delete module;
      });
    }
  }

  void reload() {
    killall();

    m_Modules = ModuleLoader::loadDirectoryRecursive<IModule>("modules/", true);
    DLOGA("Loaded %i modules", m_Modules.size());
  }

  std::string getNamesForListView() {
    std::stringstream r;
    std::for_each(m_Modules.begin(), m_Modules.end(), [&r] (IModule* module) {
      r << module->getInformation().getName() << ";";
    });
    return r.str();
  }

  uint32_t getCount() {
    return m_Modules.size();
  }
};


int main(int argc, char** argv) {
  bool bRun = true;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APPLICATION_NAME);
  SetTargetFPS(60);

  int moduleListViewSelection = -1;
  int moduleListViewScrollIndex = 0;
  int moduleListViewFocus = -1;

  Modules modules;

  while(bRun) {
    bRun = !WindowShouldClose();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    moduleListViewSelection = GuiListView(RECT {0, 0, MODULE_SCROLLER_WIDTH, SCREEN_HEIGHT},
                      modules.getNamesForListView().c_str(), &moduleListViewScrollIndex, moduleListViewSelection);

    EndDrawing();
  }

  CloseWindow();

  return ERROR_NONE;
}
