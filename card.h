#ifndef _DMINION_CARD_H_
#define _DMINION_CARD_H_

#include <deque>

namespace dminion {
namespace game {

enum CardType
{
  kTreasure = 0, //< Copper, Silver, Gold
  kVictory, //< Estate, Duchy, Province
  kKingdom, //< Action cards
  kCurse //< -1 Victory point
};

class Card
{
  int card_type;
  
public:

  void SetCardType(CardType type);
};

class Cards
{
  std::deque<Card*> cards;

public:
  Card* Pop();
  Card* PopBottom();

  void Push(Card* card);
  void PushBottom(Card* card);
  void Shuffle();
};

} // namespace game
} // namespace dminion

#endif // _DMINION_CARD_H_
