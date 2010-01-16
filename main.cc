#include "SDL/SDL.h"
#include <stdint.h>

const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kScreenDepth = 32;

int main(void)
{
  SDL_Surface *screen;

  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(kScreenWidth, kScreenHeight, kScreenDepth, 
                            SDL_HWSURFACE);
  SDL_Flip(screen);
}
