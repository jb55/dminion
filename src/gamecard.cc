#include "gamecard.h"

namespace dminion {
namespace game {

Card::Card(const string& _name, 
           const string& _description, 
           int _types,
           int _cost, 
           int _actionBonus, 
           int _cardBonus, 
           int _treasureBonus, 
           int _victoryBonus) 
             : name(_name),
               description(_description),
               types(_types),
               cost(_cost),
               actionBonus(_actionBonus),
               cardBonus(_cardBonus),
               treasureBonus(_treasureBonus),
               victoryBonus(_victoryBonus) {
}

const string& Card::GetName() const {
  return name;
}

const string& Card::GetDescription() const {
  return description;
}

int Card::GetTreasureCost() const {
  return cost;
}

int Card::GetTreasureBonus() const {
  return treasureBonus;
}

int Card::GetActionBonus() const {
  return actionBonus;
}

int Card::GetVictoryBonus() const {
  return victoryBonus;
}
  
int Card::GetCardBonus() const {
  return cardBonus;
}

int Card::GetCardTypes() const {
  return types;
}

} // namespace game
} // namespace dminion
