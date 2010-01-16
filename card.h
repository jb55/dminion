#ifndef _DMINION_CARD_H_
#define _DMINION_CARD_H_

namespace dminion {

enum CardType
{
  kTreasure = 0, //< Copper, Silver, Gold
  kVictory, //< Estate, Duchy, Province
  kKingdom, //< Action cards
  kCurse //< -1 Victory point
}

class Card
{
  int card_type;
  
public:

  void SetCardType(CardType type);
};

}

#endif // _DMINION_CARD_H_
