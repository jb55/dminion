#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include <map>

namespace dminion {
namespace resource {

struct FontKey
{
  string font;
  int ptSize;

  bool operator<(const FontKey& rhs) const {
    return font < rhs.font;
  }
};

typedef std::map<FontKey, TTF_Font*> fontResourceMap;
static fontResourceMap fontResources;

TTF_Font* GetFont(const string& name, int ptSize) {
  typedef fontResourceMap::const_iterator iterType;

  const fontResourceMap& map = fontResources;
  iterType it = fontResources.begin();

  for (it = map.begin(); it != map.end(); ++it) {
    if (it->first.font == name && it->first.ptSize == ptSize) {
      return it->second;
    }
  }

  // Font not found in cache, load it
  TTF_Font* font = font::Load(name, ptSize);

  FontKey key = { name, ptSize };
  fontResources[key] = font;

  return font;
}

} // namespace resource
} // namespace dminion
