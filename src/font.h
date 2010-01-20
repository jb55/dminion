#ifndef _DMINION_FONT_
#define _DMINION_FONT_
#include "types.h"
#include "SDL/SDL_ttf.h"

namespace dminion {
namespace font {

enum Quality {
  kSolid,
  kShaded,
  kBlended
};

extern const string kDefaultFont;

const string& GetDefault();
TTF_Font* Load(const string& file, int ptSize);

} // namespace font
} // namespace dminion

#endif // _DMINION_FONT_
