#ifndef _DMINION_RESOURCE_
#define _DMINION_RESOURCE_
#include "types.h"
#include "SDL/SDL_ttf.h"

namespace dminion {
namespace resource {

TTF_Font* GetFont(const string& name, int ptSize);

}
}

#endif // _DMINION_RESOURCE_
