#ifndef _DMINION_UTIL_H_
#define _DMINION_UTIL_H_
#include "types.h"

struct SDL_Color;
struct SDL_Surface;
struct SDL_Rect;

namespace dminion {
struct Color;

namespace util {

void PositionSurface(const SDL_Surface* surface, const Vec2& pos,
                     SDL_Rect& rect);
void ColorToSDL(const Color& color, SDL_Color* sdlColor);
uint16_t* WideToU16(const wchar_t* wide, uint16_t* u16, size_t size);
char* WideToChar(const wchar_t* wide, char* ch, size_t size);

} // namespace util
} // namespace dminion

#endif // _DMINION_UTIL_H_

