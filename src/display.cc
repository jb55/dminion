#include "display.h"
#include "settings.h"
#include "resource.h"
#include "gamecard.h"
#include "font.h"
#include "util.h"
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
  screen = SDL_SetVideoMode(width, height, depth, SDL_SWSURFACE);
#endif

  initialized = true;
}

void Display::Flip() {
#ifndef NORENDER
  SDL_Flip(screen);
#endif
}

void Display::DrawText(const string& text, const Vec2& pos, 
                       const Color& color, int ptSize) {
  TTF_Font* font;
  SDL_Surface* renderedText;
  font = resource::GetFont(font::GetDefault(), ptSize);

  renderedText = util::DrawTextToSurface(font, text, color);

  SDL_Rect dstRect;
  util::PositionSurface(renderedText, pos, dstRect, screen);

  SDL_BlitSurface(renderedText, NULL, screen, &dstRect);
  SDL_FreeSurface(renderedText);
}

void Display::DrawCard(game::Card* card, const Vec2& pos) {
  Texture cardTexture = resource::GetCardTexture(card);  

  SDL_Rect dstRect;
  util::PositionSurface(cardTexture, pos, dstRect, screen);

  SDL_BlitSurface(cardTexture, NULL, screen, &dstRect);
}

Display::Display() : initialized(false) {
}

Display::~Display() {
  if (initialized) {
    // destroy
  }
}

}
