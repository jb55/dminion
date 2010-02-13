#ifndef _DMINION_CARD_H_
#define _DMINION_CARD_H_

#include "types.h"
#include "GL/gl.h"
#include <deque>

struct SDL_Surface;

namespace dminion {
namespace game { class Card; }
namespace card {

game::Card* Load(const string& name);
int GetFlagByName(const string& name);
int* GetBonusFieldByName(const string& name, game::Card* card);
Texture LoadTexture(game::Card* card);
void LoadAll();

const string& GetBonusString(int bonusType);
const string& GetBonusTextureString(int bonusType);

string GetTypeString(game::Card* card);

} // namespace card
} // namespace dminion

#endif // _DMINION_CARD_H_
