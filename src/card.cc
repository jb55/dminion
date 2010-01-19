#include <fstream>
#include <iostream>
#include "gamecard.h"
#include "card.h"
#include "resource.h"
#include "yaml-cpp/yaml.h"

namespace dminion {
namespace card {

struct CardFlagPair {
  string name;
  int flag;
};

struct CardBonusPair {
  string name;
  int game::Card::*p;
};

static const CardFlagPair kCardFlagMap[] = {
  { "treasure", game::Card::kTreasure },
  { "victory", game::Card::kVictory },
  { "action", game::Card::kAction },
  { "attack", game::Card::kAttack },
  { "curse", game::Card::kCurse },
  { "duration", game::Card::kDuration },
  { "defense", game::Card::kDefense }
};

int GetCardFlagByName(const string& name) {
  for (size_t i = 0; i < sizeof(kCardFlagMap); ++i) {
    if (kCardFlagMap[i].name == name) {
      return kCardFlagMap[i].flag;
    }
  }
  return game::Card::kNone;
}

void LoadAll() {
  Load("cards/custom/test.yaml");
}

template <typename T>
static inline void SetKeyIfExists(const YAML::Node& node, const string& key,
    T& val, bool warnIfMissing = false,
    const string& filename = "") {
  if (const YAML::Node* subNode = node.FindValue(key)) {
    *subNode >> val;
  } else if (warnIfMissing) {
    std::cout << "Warning - missing field '" << key << "' in " << filename;
  }
}

game::Card* Load(const string& name) {
  std::string parsedName, description;
  const std::string filename = "cards/custom/test.yaml";
  std::ifstream fin(filename.c_str());
  YAML::Parser parser(fin);
  YAML::Node doc;

  int flags = game::Card::kNone;
  int cost = 0;
  int actionBonus = 0;
  int cardBonus = 0;
  int treasureBonus = 0;
  int victoryBonus = 0;

  game::Card* card;

  while (parser.GetNextDocument(doc)) {
    string val;

    SetKeyIfExists<string>(doc, "name", parsedName, true, filename);
    SetKeyIfExists<string>(doc, "description", description);

    // Load bonuses
    if (const YAML::Node* bonuses = doc.FindValue("bonuses")) {
      SetKeyIfExists<int>(*bonuses, "action", actionBonus);
      SetKeyIfExists<int>(*bonuses, "card", cardBonus); 
      SetKeyIfExists<int>(*bonuses, "treasure", treasureBonus);
      SetKeyIfExists<int>(*bonuses, "victory", victoryBonus);
    }

    // Load types
    const YAML::Node& types = doc["types"];
    for (size_t i = 0; i < types.size(); ++i) {
      types[i] >> val;
      flags |= GetCardFlagByName(val);
    }
  }

  card = new game::Card(parsedName, description, flags, cost, actionBonus, 
      cardBonus, treasureBonus, victoryBonus); 

  resource::AddCard(card);

  std::cout << "Card Loaded: " << card->GetName() << std::endl;
  std::cout << "Description: " << card->GetDescription() << std::endl;

  return card;
}

} // namespace card
} // namespace dminion
