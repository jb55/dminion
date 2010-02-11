#ifndef _DMINION_UTIL_H_
#define _DMINION_UTIL_H_
#include "types.h"
#include "const.h"
#include "font.h"

struct SDL_Color;
struct SDL_Surface;
struct SDL_Rect;

namespace dminion {
struct Color;

namespace util {

Texture       SurfaceToTexture(SDL_Surface* surface, bool needsBase=true);
SDL_Surface*  LoadImage(const string& filename);

void          PositionSurface(SDL_Surface* surface, const Vec2& pos, 
                              SDL_Rect& rect, SDL_Surface* dstSurface, 
                              font::Alignment align = font::kLeft);

void          ColorToSDL(const Color& color, SDL_Color* sdlColor);
uint16_t*     WideToU16(const wchar_t* wide, uint16_t* u16, size_t size);
char*         WideToChar(const wchar_t* wide, char* ch, size_t size);

unsigned int  CountBitsSet(unsigned int flags);

void FormatStats(int* bonus, StatList& stats);
bool FormatDescription(const string& description, std::vector<string>& lines,
                       size_t breakSize = 30);

TextureSize DrawTextToSurface(SDL_Surface* dstSurface,
                              const Vec2& pos,
                              TTF_Font* font,
                              const string& text,
                              font::Alignment align,
                              const Color& fgColor=globals::black,
                              const Color& bgColor=globals::white,
                              font::Quality quality=font::kBlended);
} // namespace util
} // namespace dminion

#endif // _DMINION_UTIL_H_

