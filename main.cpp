#include <iostream>
#include <vector>

#include <raylib.h>

#include "libs/UI/Toast/Toast.h"
#include "libs/Manager/Manager.h"
#include "libs/GPS/GPS.h"
#include "libs/Network/Network.h"
#include "libs/Configuration/Configuration.h"
#include "libs/UI/ViewManager/ViewManager.h"


int main(int argc, char** argv) {
    Configuration* cfg;
    if(argc == 1) cfg = Configuration::load();
    else cfg = Configuration::load(argv[1]);

    if(cfg == nullptr) {
        std::cout << "config file could not be found" << std::endl;
        return -1;
    }

    auto* mgr = new Manager(cfg);
    std::thread mgrThread = mgr->getThread();

    if(Utils::isPi()) {
        std::cout << "running on rpi" << std::endl;
        SetConfigFlags(FLAG_FULLSCREEN_MODE);
        SetConfigFlags(FLAG_WINDOW_UNDECORATED);
        InitWindow(800, 600, "carpi");
    } else {
        std::cout << "running on desktop" << std::endl;
        InitWindow(800, 600, "carpi");
    }

    if(Utils::isPi()) DisableCursor();
    SetTargetFPS(80);

    auto *vm = new ViewManager(mgr);

    while(mgr->getDoRun() && !WindowShouldClose()){
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        vm->loop(mgr);
        DrawFPS(8, 576);
        EndDrawing();
    }

    CloseWindow();

    mgr->stop();
    mgrThread.join();
    cfg->dump();

    return 0;
}