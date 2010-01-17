#include "display.h"
#include "settings.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

namespace dminion {

void Display::Init() {
  Settings* settings = GetSettings();

  const int width = settings->GetInt(L"window.width");
  const int height = settings->GetInt(L"window.height");
  const int depth = settings->GetInt(L"window.depth");

  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE);

  initialized = true;
}

void Display::Flip() {
  SDL_Flip(screen);
}

void Display::DrawText(const string& text, const Vec2& pos) {
  
}

Display::Display() : initialized(false) {
}

Display::~Display() {
  if (initialized) {
    // destroy
  }
}

}
