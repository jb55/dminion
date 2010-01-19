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
  screen = SDL_SetVideoMode(width, height, depth, SDL_HWSURFACE);
#endif

  initialized = true;
}

void Display::Flip() {
#ifndef NORENDER
  SDL_Flip(screen);
#endif
}

void Display::DrawText(const string& text, const Vec2& pos, int ptSize) {
  TTF_Font* font;
  SDL_Surface* renderedText;
  const string kFont = "/usr/share/fonts/truetype/freefont/FreeSerif.ttf";
  font = resource::GetFont(kFont, ptSize);

  const Color white(255, 255, 255);
  const Color black(0, 0, 0);
  renderedText = font::DrawTextToSurface(
                 font, white, black, text, font::kBlended);

  SDL_Rect dstRect;
  util::PositionSurface(renderedText, pos, dstRect);

  SDL_BlitSurface(renderedText, NULL, screen, &dstRect);
  SDL_FreeSurface(renderedText);
}

void Display::DrawCard(const game::Card* card, const Vec2& pos) {
  SDL_Surface* templateCard;
  static const string kTemplateFile = "img/card_template_tiny.png";
  templateCard = resource::GetImage(kTemplateFile);  

  SDL_Rect dstRect;
  util::PositionSurface(templateCard, pos, dstRect);

  // Pink is transparent
  SDL_BlitSurface(templateCard, NULL, screen, &dstRect);
}

Display::Display() : initialized(false) {
}

Display::~Display() {
  if (initialized) {
    // destroy
  }
}

}
