#ifndef _DMINION_DISPLAY_H_
#define _DMINION_DISPLAY_H_

#include "SDL/SDL.h"

namespace dminion {

class Display 
{
  SDL_Surface* surface;
  bool initialized;

public:

  Display();
  ~Display();
  
  void Init();

};

}

#endif // _DMINION_DISPLAY_H_
