#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include "card.h"
#include "gamecard.h"
#include "const.h"
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
  static const string kCardTemplate = "card_template.png";
  SDL_Rect dstRect;
  SDL_Surface* base;
  SDL_Surface* cardText;
  SDL_Surface* cardTemplate;

  cardTemplate = resource::GetTexture(kCardTemplate);
  
  SDL_PixelFormat* fmt = cardTemplate->format;
  base = SDL_CreateRGBSurface(SDL_SWSURFACE, 
                              cardTemplate->w, cardTemplate->h, 
                              fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask,
                              fmt->Bmask, fmt->Amask);
  
  // I don't know what these do but it makes it work so I'm not complaining
  SDL_SetAlpha(base, 0, base->format->alpha);

  // Card art
  SDL_Surface* cardArt = resource::GetTexture(card->GetArt());
  util::PositionSurface(cardArt, Vec2(0, 60), dstRect, base, kCenter);
  if (SDL_BlitSurface(cardArt, NULL, base, &dstRect) < 0) {
    std::cout << "Error blitting card art to base" << std::endl;
  }

  //SDL_SetAlpha(cardTemplate, 0, alpha);

  // Card template
  if (SDL_BlitSurface(cardTemplate, NULL, base, NULL) < 0) {
    std::cout << "Error blitting card template to base" << std::endl;
  }

  // Card name
  TTF_Font* font = resource::GetFont(font::GetDefault(), 32);
  cardText = util::DrawTextToSurface(font, card->GetName(), globals::black);
  util::PositionSurface(cardText, Vec2(0, 25), dstRect, base, kCenter);

  SDL_BlitSurface(cardText, NULL, base, &dstRect);
  SDL_FreeSurface(cardText);

  // Card stats
  font = resource::GetFont(font::GetDefault(), 18);
  cardText = util::DrawTextToSurface(font, card::GetTypeString(card), 
                                     globals::black);
  SDL_FreeSurface(cardText);

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
  static const string kTextureDir = "img/";
  return textureManager.Get(kTextureDir + name);
}

void AddCard(game::Card* card) {
  cardManager.Add(card->GetName(), card);
}

game::Card* GetCard(const string& name) {
  return cardManager.Get(name);
}

} // namespace resource
} // namespace dminion
