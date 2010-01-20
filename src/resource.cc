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
  Texture id;

  surface = util::LoadImage(name);
  id = util::SurfaceToTexture(surface);
  SDL_FreeSurface(surface);
  
  return id;
}

Texture CardTextureManager::Load(const game::Card*& card, const int& unused) {
  static const string kCardTemplate = "img/card_template_big.png";
  SDL_Surface* base;
  SDL_Surface* cardNameText;
  SDL_Surface* cardTemplate;

  cardTemplate = util::LoadImage(kCardTemplate);
  SDL_PixelFormat* fmt = cardTemplate->format;
  base = SDL_CreateRGBSurface(SDL_SWSURFACE, cardTemplate->w, cardTemplate->h, 
                              32, fmt->Bmask, fmt->Gmask, fmt->Rmask, 
                              fmt->Amask);

  // TODO: Render card art

  // Render card template
  SDL_BlitSurface(cardTemplate, NULL, base, NULL);

  // Render text
  TTF_Font* font = resource::GetFont(font::GetDefault(), 16);
  cardNameText = util::DrawTextToSurface(font, card->GetName());
  
  return base;
}

game::Card* CardManager::Load(const string& key, const string& set) {
  return card::Load(key);
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
