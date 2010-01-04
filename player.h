#ifndef DMINION_PLAYER_H_
#define DMINION_PLAYER_H_

#include <list>

namespace dminion {

class Card;

class Player
{
  std::vector<Card*> hand;
  std::vector<Card*> graveyard;
  std::vector<Card*> deck;

public:


};

}

#endif
