#include "display.h"
#include "settings.h"
#include <iostream>

namespace dminion {

void Display::Init() {
  Settings* settings = GetSettings();

  const int width = settings->GetInt(L"window.width");
  const int height = settings->GetInt(L"window.height");
  const int depth = settings->GetInt(L"window.depth");

  SDL_Init(SDL_INIT_VIDEO);
  surface = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE);

  initialized = true;
}

void Display::Flip() {
  SDL_Flip(surface);
}

Display::Display() : initialized(false) {
}

Display::~Display() {
  if (initialized) {
    // destroy
  }
}

}
