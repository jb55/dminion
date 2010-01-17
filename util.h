#ifndef _DMINION_UTIL_H_
#define _DMINION_UTIL_H_
#include "types.h"

struct SDL_Color;

namespace dminion {
struct Color;

namespace util {

void ColorToSDL(const Color& color, SDL_Color* sdlColor);
uint16_t* WideToU16(const wchar_t* wide, uint16_t* u16, size_t size);
char* WideToChar(const wchar_t* wide, char* ch, size_t size);

} // namespace util
} // namespace dminion

#endif // _DMINION_UTIL_H_

