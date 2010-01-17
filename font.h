#ifndef _DMINION_FONT_
#define _DMINION_FONT_
#include "types.h"
#include "SDL/SDL_ttf.h"

namespace dminion {
namespace util {

TTF_Font* LoadFont(const string& file, int ptSize);

}
}

#endif // _DMINION_FONT_
