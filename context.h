#ifndef _DMINION_CONTEXT_H_
#define _DMINION_CONTEXT_H_

#include "player.h"
#include <list>

namespace dminion {
namespace game {

enum State {
  kDrawHandState,
  kActionState,
  kBuyState
};

class Context
{
  int playerTurn;
  State state;
  std::list<Player> players;

public:

  Context();

  int   GetPlayerTurn() const;
  State GetGameState() const; 
  
  Player& GetPlayer(int num);
};

} // namespace game
} // namespace dminion

#endif // _DMINION_CONTEXT_H_
