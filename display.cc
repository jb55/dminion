#include "display.h"
#include "settings.h"
#include "resource.h"
#include "font.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

namespace dminion {

void Display::Init() {
  Settings* settings = GetSettings();

  const int width = settings->GetInt("window.width");
  const int height = settings->GetInt("window.height");
  const int depth = settings->GetInt("window.depth");

#ifndef NORENDER
  TTF_Init();

  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE);
#endif

  initialized = true;
}

void Display::Flip() {
#ifndef NORENDER
  SDL_Flip(screen);
#endif
}

void Display::DrawText(const string& text, const Vec2& pos) {
  TTF_Font* font;
  SDL_Surface* renderedText;
  const string kFont = "/usr/share/fonts/truetype/freefont/FreeSerif.ttf";
  font = resource::GetFont(kFont, 32);

  const Color white(255, 255, 255);
  const Color black(0, 0, 0);
  renderedText = font::DrawTextToSurface(
                 font, white, black, text, font::kBlended);

  SDL_Rect dstRect = {
    (short)pos.x, (short)pos.y,
    renderedText->w, renderedText->h
  };

  SDL_BlitSurface(renderedText, NULL, screen, &dstRect);
  SDL_FreeSurface(renderedText);
}

Display::Display() : initialized(false) {
}

Display::~Display() {
  if (initialized) {
    // destroy
  }
}

}
