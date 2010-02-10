#include <fstream>
#include <iostream>
#include "gamecard.h"
#include "card.h"
#include "resource.h"
#include "yaml-cpp/yaml.h"

namespace dminion {
namespace card {
namespace {

struct CardPair {
  string name;
  int val;
};

const CardPair kCardFlagMap[] = {
  { "treasure", game::Card::kTreasure },
  { "victory", game::Card::kVictory },
  { "action", game::Card::kAction },
  { "attack", game::Card::kAttack },
  { "curse", game::Card::kCurse },
  { "duration", game::Card::kDuration },
  { "defense", game::Card::kDefense }
};

const CardPair kCardBonusMap[] = {
  { "", game::kTreasureBonus }, // icon
  { "", game::kVictoryBonus }, // icon
  { "Action", game::kActionBonus },
  { "Card", game::kCardBonus }
};

template <typename T>
inline void SetKeyIfExists(const YAML::Node& node, const string& key,
                                  T& val, bool warnIfMissing = false,
                                  const string& filename = "") {
  if (const YAML::Node* subNode = node.FindValue(key)) {
    *subNode >> val;
  } else if (warnIfMissing) {
    std::cout << "Warning - missing field '" << key << "' in " << filename;
  }
}

} // anonymous namespace

int GetCardFlagByName(const string& name) {
  for (size_t i = 0; i < sizeof(kCardFlagMap); ++i) {
    if (kCardFlagMap[i].name == name) {
      return kCardFlagMap[i].val;
    }
  }
  return game::Card::kNone;
}

const string& GetBonusString(int bonusType) {
  for (size_t i = 0; i < sizeof(kCardBonusMap); ++i) {
    if (kCardBonusMap[i].val == bonusType) {
      return kCardFlagMap[i].name;
    }
  }
  return kCardBonusMap[game::kTreasureBonus].name;
}

void LoadAll() {
  resource::GetCard("custom/test");
}

string GetTypeString(game::Card* card) {
  string strTypes;
  int types = card->GetCardTypes();
  
  if (types & game::Card::kTreasure)  strTypes.append("Treasure - ");
  if (types & game::Card::kVictory)   strTypes.append("Victory - ");
  if (types & game::Card::kAction)    strTypes.append("Action - ");
  if (types & game::Card::kDefense)   strTypes.append("Defense - ");
  if (types & game::Card::kAttack)    strTypes.append("Attack - ");
  if (types & game::Card::kCurse)     strTypes.append("Curse - ");
  if (types & game::Card::kDuration)  strTypes.append("Curse - ");

  size_t size = 0;
  if ((size = strTypes.size()) > 2) {
    strTypes.resize(size - 3);
  }

  return strTypes;
}

game::Card* Load(const string& name) {
  string parsedName, description, art;

  std::ifstream fin(name.c_str());
  YAML::Parser parser(fin);
  YAML::Node doc;

  int flags = game::Card::kNone;
  int cost = 0;
  int bonus[game::kNumBonuses];

  game::Card* card;

  while (parser.GetNextDocument(doc)) {
    string val;

    SetKeyIfExists(doc, "name", parsedName, true, name);
    SetKeyIfExists(doc, "cost", cost, true, name);
    SetKeyIfExists(doc, "description", description);
    SetKeyIfExists(doc, "art", art, true, name);

    // Load bonuses
    if (const YAML::Node* bonuses = doc.FindValue("bonuses")) {
      SetKeyIfExists(*bonuses, "action", bonus[game::kActionBonus]);
      SetKeyIfExists(*bonuses, "card", bonus[game::kCardBonus]); 
      SetKeyIfExists(*bonuses, "treasure", bonus[game::kTreasureBonus]);
      SetKeyIfExists(*bonuses, "victory", bonus[game::kVictoryBonus]);
    }

    // Load types
    const YAML::Node& types = doc["types"];
    for (size_t i = 0; i < types.size(); ++i) {
      types[i] >> val;
      flags |= GetCardFlagByName(val);
    }
  }

  card = new game::Card(parsedName, description, art, flags, cost, bonus); 

  std::cout << "Card Loaded: " << card->GetName() << std::endl;
  std::cout << "Description: " << card->GetDescription() << std::endl;

  return card;
}

} // namespace card
} // namespace dminion
