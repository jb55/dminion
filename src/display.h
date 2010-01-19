#ifndef _DMINION_DISPLAY_H_
#define _DMINION_DISPLAY_H_
#include "types.h"

struct SDL_Surface;

namespace dminion {

class Display 
{
  SDL_Surface* screen;
  bool initialized;

public:

  Display();
  ~Display();

  void DrawText(const string& text, const Vec2& pos);
  
  void Init();
  void Flip();

};

}

#endif // _DMINION_DISPLAY_H_
