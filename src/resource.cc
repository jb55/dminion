#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include "card.h"
#include "gamecard.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <map>

namespace dminion {
namespace resource {

static FontManager fontManager;
static TextureManager textureManager;
static CardTextureManager cardTextureManager;
static CardManager cardManager;

TTF_Font* FontManager::Load(const string& name, const int& ptSize) {
  return font::Load(name, ptSize);
}

Texture TextureManager::Load(const string& name, const int& unused) {
  SDL_Surface* surface;

  surface = util::LoadImage(name);
  return surface;
}

Texture CardTextureManager::Load(game::Card* const& card, const int& unused) {
  static const string kCardTemplate = "img/card_template_big.png";
  SDL_Rect dstRect;
  SDL_Surface* base;
  SDL_Surface* cardNameText;
  SDL_Surface* cardTemplate;
  SDL_Surface* converted;

  cardTemplate = resource::GetTexture(kCardTemplate);
  
  SDL_PixelFormat* fmt = cardTemplate->format;
  base = SDL_CreateRGBSurface(SDL_SWSURFACE, 
                              cardTemplate->w, cardTemplate->h, 
                              fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask,
                              fmt->Bmask, fmt->Amask);
  
  // I don't know what these do but it makes it work so I'm not complaining
  SDL_SetAlpha(cardTemplate, 0, fmt->alpha);
  SDL_SetAlpha(base, SDL_SRCALPHA, base->format->alpha);

  // TODO: Render card art

  // Render card template
  if (SDL_BlitSurface(cardTemplate, NULL, base, NULL) < 0) {
    std::cout << "Error blitting card template to base" << std::endl;
  }

  // Render text
  // Card name
  TTF_Font* font = resource::GetFont(font::GetDefault(), 32);
  cardNameText = util::DrawTextToSurface(font, card->GetName(), util::black);
  util::PositionSurface(cardNameText, Vec2(20, 25), dstRect);

  if (SDL_BlitSurface(cardNameText, NULL, base, &dstRect)) {
    std::cout << "Error blitting card name text to base" << std::endl;
  }

  SDL_FreeSurface(cardNameText);

  // Card name
  return base;
}

game::Card* CardManager::Load(const string& key, const int& unused) {
  static const string kCardDir = "cards/";
  static const string kCardExt = ".yaml";
  return card::Load(kCardDir + key + kCardExt);
}

TTF_Font* GetFont(const string& name, int ptSize) {
  return fontManager.Get(name, ptSize);
}

Texture GetCardTexture(game::Card* card) {
  return cardTextureManager.Get(card);
}

Texture GetTexture(const string& name) {
  return textureManager.Get(name);
}

void AddCard(game::Card* card) {
  cardManager.Add(card->GetName(), card);
}

game::Card* GetCard(const string& name) {
  return cardManager.Get(name);
}

} // namespace resource
} // namespace dminion
