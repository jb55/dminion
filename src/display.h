#ifndef _DMINION_DISPLAY_H_
#define _DMINION_DISPLAY_H_
#include "types.h"

struct SDL_Surface;

namespace dminion {
namespace game { class Card; }

class Display 
{
  SDL_Surface* screen;
  bool initialized;

public:

  Display();
  ~Display();

  void DrawText(const string& text, const Vec2& pos, int ptSize = 32);
  void DrawCard(game::Card* card, const Vec2& pos);
  
  void Init();
  void Flip();

};

}

#endif // _DMINION_DISPLAY_H_
