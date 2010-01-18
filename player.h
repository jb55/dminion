#ifndef DMINION_PLAYER_H_
#define DMINION_PLAYER_H_

#include <vector>

namespace dminion {
namespace game {

class Card;

class Player
{
  std::vector<Card*> hand;
  std::vector<Card*> graveyard;
  std::vector<Card*> deck;

public:


};

} // namespace game
} // namespace dminion

#endif // DMINION_PLAYER_H_
