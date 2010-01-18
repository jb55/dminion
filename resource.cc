#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include "card.h"
#include <vector>

namespace dminion {
namespace resource {

template <typename T>
struct ResourceEntry {
  ResourceEntry(const string& _name, T& _data) : name(_name), data(_data) {}
  string name;
  T data;
};

struct FontEntry : ResourceEntry<TTF_Font*> {
  FontEntry(const string& _name, TTF_Font*& _data, int _ptSize) 
    : ResourceEntry<TTF_Font*>(_name, _data), ptSize(_ptSize) {}
  int ptSize;
};

template <typename T>
struct Resource {
  typedef std::vector<ResourceEntry<T> > Type;
};

typedef std::vector<FontEntry> FontResource;
typedef Resource<game::Card*>::Type CardResource;

static FontResource fontResources;
static CardResource cardResources;

template <typename T>
T getResourceByName(const string& name, 
                    const typename Resource<T>::Type& resource) {
  typename Resource<T>::Type::const_iterator it;
  for (it = resource.begin(); it != resource.end(); ++it) {
    if (it->name == name) {
      return it->data;
    }
  }
  return 0;
}

TTF_Font* GetFont(const string& name, int ptSize) {
  const std::vector<FontEntry>& fonts = fontResources;
  std::vector<FontEntry>::const_iterator it;

  for (it = fonts.begin(); it != fonts.end(); ++it) {
    if (it->name == name && it->ptSize == ptSize) {
      return it->data;
    }
  }

  // Font not found in cache, load it
  TTF_Font* font = font::Load(name, ptSize);

  FontEntry key(name, font, ptSize);
  fontResources.push_back(key);

  return font;
}

game::Card* GetCard(const string& name) {
  return getResourceByName<game::Card*>(name, cardResources);
}


} // namespace resource
} // namespace dminion
