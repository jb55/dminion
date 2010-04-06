#ifndef _DMINION_CARD_H_
#define _DMINION_CARD_H_

#include "common.h"
#include "GL/gl.h"
#include <deque>

struct SDL_Surface;

namespace dminion {
class Card;
namespace card {

enum BonusType {
  kCardBonus,
  kActionBonus,
  kTreasureBonus,
  kVictoryBonus,
  kNumBonuses
};

Card* Load(const string& name);
int GetFlagByName(const string& name);
int* GetBonusFieldByName(const string& name, Card* card);
Texture LoadTexture(Card* card);
void LoadAll();

const string& GetBonusString(int bonusType);
const string& GetBonusTextureString(int bonusType);

string GetTypeString(Card* card);

} // namespace card

typedef std::deque<Card*> Cards;

class Card
{
  string name;
  string description;
  string art;
  int types;
  int cost;

  int bonus[card::kNumBonuses];

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
  int GetCardBonus(card::BonusType bonusType) const;
  int* GetBonuses();
  int GetCardTypes() const;
};

} // namespace dminion

#endif // _DMINION_CARD_H_
