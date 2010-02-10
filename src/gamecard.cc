#include "gamecard.h"

namespace dminion {
namespace game {

Card::Card(const string& _name, const string& _description, const string& _art,
           int _types, int _cost, int* bonuses) : name(_name), 
           description(_description), art(_art), types(_types), cost(_cost) {
  for (int i = 0; i < kNumBonuses; ++i) {
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
  
int Card::GetCardBonus(BonusType bonusType) const {
  return bonus[bonusType];
}

int Card::GetCardTypes() const {
  return types;
}

} // namespace game
} // namespace dminion
