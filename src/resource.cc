#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include "card.h"
#include "gamecard.h"
#include "const.h"
#include "SDL/SDL_image.h"
#include "boost/foreach.hpp"
#include "dense_pair.h"
#include <iostream>
#include <sstream>
#include <utility>
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
  static const string kCardTemplate = "card_template.png";
  int savedStyle = 0;
  SDL_Rect dstRect;
  SDL_Surface* base;
  SDL_Surface* cardTemplate;
  TTF_Font* font;

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

  // Card template
  if (SDL_BlitSurface(cardTemplate, NULL, base, NULL) < 0) {
    std::cout << "Error blitting card template to base" << std::endl;
  }

  // Card name
  font = resource::GetFont(font::GetDefault(), 32);
  util::DrawTextToSurface(base, Vec2(0, 24), font, card->GetName(), 
                          kCenter);

  // Card stats
  static const int kDescStart = 260;
  static const int kStep = 17;
  Texture victoryTexture = 0, treasureTexture = 0;
  int position = kDescStart;
  StatList stats;

  font = resource::GetFont(font::GetSans(), 18);
  savedStyle = TTF_GetFontStyle(font);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  util::FormatStats(card->GetBonuses(), stats);

  int i = 0;
  foreach (Stat stat, stats) {
    position += kStep * 1.3;
    TextureSize size;
    util::DrawTextToSurface(base, Vec2(0, position), font, stat.first,
                                   kCenter, &dstRect);
    int bonus = stat.second;
    SDL_Surface* texture;
    bool hasIcon = bonus != game::kNumBonuses;
    if (hasIcon) {
      switch (bonus) {
      case game::kVictoryBonus:
        texture = victoryTexture ? victoryTexture :
                                   resource::GetTexture("victory_bonus.png");
        break;
      default:
      case game::kTreasureBonus:
        texture = treasureTexture ? treasureTexture :
                                    resource::GetTexture("treasure_bonus.png");
        break;
      }
    }

    int x = dstRect.x + dstRect.w;
    int y = dstRect.y + 3;
    util::DrawToSurface(base, texture, Vec2(x, y));
    i++;
  }

  TTF_SetFontStyle(font, savedStyle);
  position += kStep;

  // Card description
  std::vector<string> lines;
  const string& description = card->GetDescription();

  font = resource::GetFont(font::GetSans(), 14);
  bool hasLines = util::FormatDescription(card->GetDescription(), lines, 34);
  if (hasLines) {
    int i = 0;
    foreach (string line, lines) {
      position += kStep;
      util::DrawTextToSurface(base, Vec2(0, position), font,
                              line, kCenter);
      i++;
    }
  } else {
    util::DrawTextToSurface(base, Vec2(0, kDescStart), font, description,
                            kCenter);
  }

  // Card cost
  std::stringstream os;
  os << card->GetTreasureCost();

  font = resource::GetFont(font::GetSans(), 24);
  savedStyle = TTF_GetFontStyle(font);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  util::DrawTextToSurface(base, Vec2(39, 435), font, os.str(), kLeft);
  TTF_SetFontStyle(font, savedStyle);

  // Card type
  unsigned int numTypes = util::CountBitsSet(card->GetCardTypes());
  font = resource::GetFont(font::GetDefault(), 24 - numTypes * 2);
  util::DrawTextToSurface(base, Vec2(0, 435), font, card::GetTypeString(card), 
                          kCenter);

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
