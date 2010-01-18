#ifndef _DMINION_CONTEXT_H_
#define _DMINION_CONTEXT_H_

#include "player.h"
#include "card.h"
#include <vector>

namespace dminion {
namespace game {

enum State {
  kDrawHandState,
  kActionState,
  kBuyState
};

class Context
{
  Cards trash;
  Cards draft;

  int playerTurn;
  State state;
  std::vector<Player*> players;

public:
  Context();

  void StartGame();

  int   GetPlayerTurn() const;
  State GetGameState() const; 
  
  Player* GetPlayer(int num);
};

} // namespace game
} // namespace dminion

#endif // _DMINION_CONTEXT_H_
