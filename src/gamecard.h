#ifndef _DMINION_GAMECARD_H_
#define _DMINION_GAMECARD_H_

#include "types.h"
#include <deque>

namespace dminion {
namespace game {

class Card
{
  string name;
  string description;
  int types;
  int cost;

  int actionBonus;
  int cardBonus;
  int treasureBonus;
  int victoryBonus;
  
public:
  enum TypeFlags
  {
    kNone     = 1 << 0,  //< Invalid card?
    kTreasure = 1 << 1,  //< Copper, Silver, Gold
    kVictory  = 1 << 2,  //< Estate, Duchy, Province
    kAction   = 1 << 3,  //< Action cards
    kAttack   = 1 << 4,  //< Attack
    kCurse    = 1 << 5,  //< -1 Victory point
    kDuration = 1 << 6,  //< Lasts until next turn
    kDefense  = 1 << 7,  //< Reaction against attacks
  };

  Card(const string& name, const string& description, int types,
       int cost, int actionBonus, int cardBonus, int treasureBonus, 
       int victoryBonus);

  const string& GetName() const;
  const string& GetDescription() const;

  int GetGoldCost() const;
  int GetGoldBonus() const;
  int GetActionBonus() const;
  int GetVictoryBonus() const;
  int GetCardBonus() const;
  int GetCardType() const;
};

class Cards
{
  std::deque<Card*> cards;

public:
  Card* Pop();
  Card* PopBottom();

  void Push(Card* card);
  void PushFront(Card* card);
  void Shuffle();
};

} // namespace game
} // namespace dminion

#endif // _DMINION_GAMECARD_H_
