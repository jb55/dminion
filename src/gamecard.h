#ifndef _DMINION_GAMECARD_H_
#define _DMINION_GAMECARD_H_

#include "types.h"
#include <deque>

namespace dminion {
namespace game {

enum BonusType {
  kActionBonus,
  kCardBonus,
  kTreasureBonus,
  kVictoryBonus,
  kNumBonuses
};

class Card
{
  string name;
  string description;
  string art;
  int types;
  int cost;

  int bonus[kNumBonuses];

public:
  enum Types
  {
    kNone     = 1 << 0,  //< Invalid card?
    kTreasure = 1 << 1,  //< Copper, Silver, Gold
    kVictory  = 1 << 2,  //< Estate, Duchy, Province
    kAction   = 1 << 3,  //< Action cards
    kAttack   = 1 << 4,  //< Attack
    kCurse    = 1 << 5,  //< -1 Victory point
    kDuration = 1 << 6,  //< Lasts until next turn
    kDefense  = 1 << 7   //< Reaction against attacks
  };

  Card(const string& name, const string& description, const string& art, 
       int types, int cost, int* bonuses);

  const string& GetName() const;
  const string& GetArt() const;
  const string& GetDescription() const;

  int GetTreasureCost() const;
  int GetCardBonus(BonusType bonusType) const;
  int GetCardTypes() const;
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
