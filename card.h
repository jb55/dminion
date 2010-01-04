
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
