#include "display.h"
#include "settings.h"
#include "resource.h"
#include "font.h"
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
  TTF_Font* font;
  SDL_Surface* renderedText;
  const string kFont = L"/usr/share/fonts/truetype/freefont/FreeSerif.ttf";
  font = resource::GetFont(kFont, 10);

  const Color white(255, 255, 255);
  const Color black(0, 0, 0);
  renderedText = font::DrawTextToSurface(
                 font, white, black, text, font::kBlended);

  SDL_Rect dstRect = {
    (short)pos.x, (short)pos.y,
    renderedText->w, renderedText->h
  };

  SDL_BlitSurface(renderedText, NULL, screen, &dstRect);
}

Display::Display() : initialized(false) {
}

Display::~Display() {
  if (initialized) {
    // destroy
  }
}

}
