#ifndef _DMINION_RESOURCE_
#define _DMINION_RESOURCE_
#include "types.h"
#include "card.h"
#include "SDL/SDL_ttf.h"

namespace dminion {
namespace resource {

TTF_Font* GetFont(const string& name, int ptSize);
game::Card* GetCard(const string& name);

}
}

#endif // _DMINION_RESOURCE_
