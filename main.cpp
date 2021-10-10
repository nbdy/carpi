//
// Created by nbdy on 10.10.21.
//

#include "config.h"

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  auto *w = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_OPENGL);
  if(w == nullptr) {
    ELOG("Could not open window.");

  }

}
