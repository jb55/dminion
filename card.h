#ifndef _DMINION_CARD_H_
#define _DMINION_CARD_H_

#include "types.h"
#include <deque>

namespace dminion {

namespace game {
  class Card;
}

game::Card* LoadCard(const string& name);
void LoadCards();
namespace game {

class Card
{
  friend Card* dminion::LoadCard(const string& name);

  string name;
  string description;
  int cardType;
  int goldCost;

  int actionBonus;
  int cardBonus;
  int goldBonus;
  int victoryBonus;
  
public:
  enum Type
  {
    kTreasure = 0,  //< Copper, Silver, Gold
    kVictory,       //< Estate, Duchy, Province
    kKingdom,       //< Action cards
    kCurse          //< -1 Victory point
  };

  const string& GetName() const;
  const string& GetDescription() const;

  int GetGoldCost() const;
  int GetGoldBonus() const;
  int GetActionBonus() const;
  int GetVictoryBonus() const;
  int GetCardBonus() const;
  Type GetCardType() const;
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

#endif // _DMINION_CARD_H_
