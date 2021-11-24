//
// Created by nbdy on 10.10.21.
//

#include "carpi_config.h"
#include "CMM.h"


int main(int argc, char** argv) {
  bool bRun = true;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APPLICATION_NAME);
  SetTargetFPS(60);

  int moduleListViewSelection = -1;
  int moduleListViewScrollIndex = 0;
  int moduleListViewPreviousSelection = moduleListViewSelection;

  CMM moduleManager("modules/");

  std::function<void()> fCheckModuleSelection = [&moduleManager, &moduleListViewSelection, &moduleListViewScrollIndex, &moduleListViewPreviousSelection]{
    static IModule* drawModule = nullptr;

    moduleListViewPreviousSelection = moduleListViewSelection;
    moduleListViewSelection = GuiListView(Rectangle {0, 0, MODULE_SCROLLER_WIDTH, SCREEN_HEIGHT},
                                          moduleManager.getModuleNamesDelimited(";").c_str(), &moduleListViewScrollIndex, moduleListViewSelection);
    if(moduleListViewSelection != moduleListViewPreviousSelection) {
      if(!moduleManager.getModuleByIndex(moduleListViewSelection, drawModule)) {
        WLOGA("Could not find module at index %i", moduleListViewSelection);
      }
    }

    if(drawModule != nullptr) {
      drawModule->draw(MODULE_SCROLLER_WIDTH, 0);
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
