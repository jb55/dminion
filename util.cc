#include <stdlib.h>
#include "util.h"
#include "SDL/SDL.h"
#include "types.h" 

namespace dminion {
namespace util {

void ColorToSDL(const Color& color, SDL_Color* sdlColor) {
	sdlColor->r = color.r;
	sdlColor->g = color.g;
	sdlColor->b = color.b;
}

uint16_t* WideToU16(const wchar_t* wide, 
										uint16_t* u16, 
										size_t size) {
	if (sizeof(wchar_t) == sizeof(uint16_t)) {
		return reinterpret_cast<uint16_t*>(const_cast<wchar_t*>(wide));
	}

	for (size_t i = 0; i < size; ++i) {
		u16[i] = static_cast<uint16_t>(wide[i]);
	}

	u16[size] = '\0';
	return u16;
}

char* WideToChar(const wchar_t* wide, char* ch, size_t size) {
	wcstombs(ch, wide, size);
  ch[size] = '\0';
	return ch;
}

} // namespace util
} // namespace dminion
