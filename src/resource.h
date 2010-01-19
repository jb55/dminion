#ifndef _DMINION_RESOURCE_
#define _DMINION_RESOURCE_
#include "types.h"
#include "SDL/SDL_ttf.h"

namespace dminion {
namespace game { class Card; }

namespace resource {

TTF_Font* GetFont(const string& name, int ptSize);
SDL_Surface* GetImage(const string& name);
game::Card* GetCard(const string& name);
void AddCard(game::Card* card);

} // namespace resource
} // namespace dminion

#endif // _DMINION_RESOURCE_
