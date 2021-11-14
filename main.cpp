//
// Created by nbdy on 10.10.21.
//

#define RAYGUI_IMPLEMENTATION
#include "ext/raygui.h"

#include "carpi_config.h"
#include "ext/modulepp.h"

#define RECT (Rectangle)


int main(int argc, char** argv) {
  bool bRun = true;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APPLICATION_NAME);
  SetTargetFPS(60);

  int moduleListViewSelection = -1;
  int moduleListViewScrollIndex = 0;
  int moduleListViewFocus = -1;

  auto modules = ModuleLoader::loadDirectory<IModule>("modules/", true);
  std::vector<const char*> moduleNames;
  moduleNames.reserve(modules.size());
  for(auto module : modules) {
    moduleNames.push_back(module->getName().c_str());
  }

  std::cout << "loaded " << modules.size() << " modules";

  while(bRun) {
    bRun = !WindowShouldClose();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    moduleListViewSelection = GuiListViewEx(RECT {0, 0, MODULE_SCROLLER_WIDTH, SCREEN_HEIGHT},
                      &moduleNames[0], (int) moduleNames.size(), &moduleListViewFocus, &moduleListViewScrollIndex, moduleListViewSelection);

    EndDrawing();
  }

  CloseWindow();

  return ERROR_NONE;
}
