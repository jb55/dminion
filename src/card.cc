#include <fstream>
#include <iostream>
#include "common.h"
#include "util.h"
#include "card.h"
#include "dense_pair.h"
#include "boost/foreach.hpp"
#include "resource.h"
#include "log.h"
#include "yaml-cpp/yaml.h"

namespace dminion {
namespace card {
namespace {

struct CardPair {
  string name;
  int val;
};

const CardPair kCardFlagList[] = {
  { "treasure", Card::kTreasure },
  { "victory", Card::kVictory },
  { "action", Card::kAction },
  { "attack", Card::kAttack },
  { "curse", Card::kCurse },
  { "duration", Card::kDuration },
  { "defense", Card::kDefense }
};

const string kBonusStrings[] = {
  "Card",
  "Action",
  "", 
  ""
};

const string kBonusTextureStrings[] = {
  "card_bonus.png",
  "action_bonus.png",
  "treasure_bonus.png",
  "victory_bonus.png"
};

template <typename T>
inline void SetKeyIfExists(const YAML::Node& node, const string& key,
                           T& val, bool warnIfMissing = false,
                           const string& filename = "") {
  if (const YAML::Node* subNode = node.FindValue(key)) {
    *subNode >> val;
  } else if (warnIfMissing) {
    WARN2("missing field '%1%' in %2%", key % filename);
  }
}

} // anonymous namespace

int GetCardFlagByName(const string& name) {
  for (size_t i = 0; i < sizeof(kCardFlagList); ++i) {
    if (kCardFlagList[i].name == name) {
      return kCardFlagList[i].val;
    }
  }
  return Card::kNone;
}

const string& GetBonusTextureString(int bonusType) {
  return kBonusTextureStrings[bonusType];
}

const string& GetBonusString(int bonusType) {
  return kBonusStrings[bonusType];
}

void LoadAll() {
  resource::GetCard("custom/test");
}

string GetTypeString(Card* card) {
  string strTypes;
  int types = card->GetCardTypes();
  
  if (types & Card::kTreasure)  strTypes.append("Treasure - ");
  if (types & Card::kVictory)   strTypes.append("Victory - ");
  if (types & Card::kAction)    strTypes.append("Action - ");
  if (types & Card::kDefense)   strTypes.append("Defense - ");
  if (types & Card::kAttack)    strTypes.append("Attack - ");
  if (types & Card::kCurse)     strTypes.append("Curse - ");
  if (types & Card::kDuration)  strTypes.append("Curse - ");

  size_t size = 0;
  if ((size = strTypes.size()) > 2) {
    strTypes.resize(size - 3);
  }

  return strTypes;
}

Texture LoadTexture(Card* card) {
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
    WARN("Error blitting card art to base");
  }

  // Card template
  if (SDL_BlitSurface(cardTemplate, NULL, base, NULL) < 0) {
    WARN("Error blitting card template to base");
  }

  // Card name
  font = resource::GetFont(font::GetDefault(), 32);
  util::DrawTextToSurface(base, Vec2(0, 24), font, card->GetName(), 
                          kCenter);

  // Card stats
  static const int kDescStart = 260;
  static const int kStep = 17;
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
    bool hasIcon = bonus != card::kNumBonuses;

    if (hasIcon) {
      const string& textureName = card::GetBonusTextureString(bonus);
      texture = resource::GetTexture(textureName);

      int x = dstRect.x + dstRect.w;
      int y = dstRect.y + 3;
      util::DrawToSurface(base, texture, Vec2(x, y));
    }

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
  unsigned numTypes = util::CountBitsSet(card->GetCardTypes());
  font = resource::GetFont(font::GetDefault(), 24 - numTypes * 2);
  util::DrawTextToSurface(base, Vec2(0, 435), font, GetTypeString(card), 
                          kCenter);

  return base;
}

Card* Load(const string& name) {
  string parsedName, description, art;

  std::ifstream fin(name.c_str());
  YAML::Parser parser(fin);
  YAML::Node doc;

  int flags = Card::kNone;
  int cost = 0;
  int bonus[card::kNumBonuses] = {0};

  Card* card;

  while (parser.GetNextDocument(doc)) {
    string val;

    SetKeyIfExists(doc, "name", parsedName, true, name);
    SetKeyIfExists(doc, "cost", cost, true, name);
    SetKeyIfExists(doc, "description", description);
    SetKeyIfExists(doc, "art", art, true, name);

    // Load bonuses
    if (const YAML::Node* bonuses = doc.FindValue("bonuses")) {
      SetKeyIfExists(*bonuses, "action", bonus[card::kActionBonus]);
      SetKeyIfExists(*bonuses, "card", bonus[card::kCardBonus]); 
      SetKeyIfExists(*bonuses, "treasure", bonus[card::kTreasureBonus]);
      SetKeyIfExists(*bonuses, "victory", bonus[card::kVictoryBonus]);
    }

    // Load types
    const YAML::Node& types = doc["types"];
    for (size_t i = 0; i < types.size(); ++i) {
      types[i] >> val;
      flags |= GetCardFlagByName(val);
    }
  }

  card = new Card(parsedName, description, art, flags, cost, bonus); 

  DEV2("Card Loaded: %1%", card->GetName());
  DEV2("Description: %1%", card->GetDescription());

  return card;
}

} // namespace card

Card::Card(const string& _name, const string& _description, const string& _art,
           int _types, int _cost, int* bonuses) : name(_name), 
           description(_description), art(_art), types(_types), cost(_cost) {
  for (int i = 0; i < card::kNumBonuses; ++i) {
    bonus[i] = *bonuses++;
  }
}

const string& Card::GetName() const {
  return name;
}

const string& Card::GetDescription() const {
  return description;
}

const string& Card::GetArt() const {
  return art;
}

int Card::GetTreasureCost() const {
  return cost;
}
  
int Card::GetCardBonus(card::BonusType bonusType) const {
  return bonus[bonusType];
}
  
int* Card::GetBonuses() {
  return bonus;
}

int Card::GetCardTypes() const {
  return types;
}

} // namespace dminion
