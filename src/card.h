#ifndef _DMINION_CARD_H_
#define _DMINION_CARD_H_

#include "types.h"
#include <deque>

namespace dminion {
namespace game { class Card; }
namespace card {

game::Card* Load(const string& name);
int GetFlagByName(const string& name);
int* GetBonusFieldByName(const string& name, game::Card* card);
void LoadAll();

} // namespace card
} // namespace dminion

#endif // _DMINION_CARD_H_
