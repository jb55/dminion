#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include "card.h"
#include "gamecard.h"
#include <map>

namespace dminion {
namespace resource {
namespace { 

FontManager fontManager;
TextureManager textureManager;
CardTextureManager cardTextureManager;
CardManager cardManager;

} // anonymous namespace

TTF_Font* FontManager::Load(const string& name, const int& ptSize) {
  return font::Load(name, ptSize);
}

Texture TextureManager::Load(const string& name, const int& unused) {
  SDL_Surface* surface;

  surface = util::LoadImage(name);
  return surface;
}

Texture CardTextureManager::Load(game::Card* const& card, const int& unused) {
  return card::LoadTexture(card);
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
