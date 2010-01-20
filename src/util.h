#ifndef _DMINION_UTIL_H_
#define _DMINION_UTIL_H_
#include "types.h"
#include "font.h"

struct SDL_Color;
struct SDL_Surface;
struct SDL_Rect;

namespace dminion {
struct Color;

namespace util {

extern const Color white;
extern const Color black;

Texture       SurfaceToTexture(SDL_Surface* surface, bool needsBase=true);
SDL_Surface*  LoadImage(const string& filename);

void          PositionSurface(SDL_Surface* surface, const Vec2& pos,
                              SDL_Rect& rect);

void          ColorToSDL(const Color& color, SDL_Color* sdlColor);
uint16_t*     WideToU16(const wchar_t* wide, uint16_t* u16, size_t size);
char*         WideToChar(const wchar_t* wide, char* ch, size_t size);

SDL_Surface*  DrawTextToSurface(TTF_Font* font,
                                const string& text, 
                                const Color& fgColor=black, 
                                const Color& bgColor=white, 
                                font::Quality quality=font::kBlended);

} // namespace util
} // namespace dminion

#endif // _DMINION_UTIL_H_

