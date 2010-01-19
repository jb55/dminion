#ifndef _DMINION_FONT_
#define _DMINION_FONT_
#include "types.h"
#include "SDL/SDL_ttf.h"

namespace dminion {
namespace font {

enum FontQuality {
  kSolid,
  kShaded,
  kBlended
};

SDL_Surface* DrawTextToSurface(TTF_Font* font, const Color& fgColor,
                               const Color& bgColor, const string& text,
                               FontQuality quality);

TTF_Font* Load(const string& file, int ptSize);

} // namespace font
} // namespace dminion

#endif // _DMINION_FONT_
