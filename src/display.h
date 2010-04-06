#ifndef _DMINION_DISPLAY_H_
#define _DMINION_DISPLAY_H_
#include "common.h"
#include "util.h"
#include "const.h"

struct SDL_Surface;

namespace dminion {
class Card;

class Display 
{
  SDL_Surface* screen;
  bool initialized;

public:

  Display();
  ~Display();

  void DrawText(const string& text, const Vec2& pos, 
                const Color& color = globals::white, int ptSize = 32);
  void DrawCard(Card* card, const Vec2& pos);
  
  void Init();
  void Flip();

};

}

#endif // _DMINION_DISPLAY_H_
