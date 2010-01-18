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
  ResourceEntry(const string& _name, T& _data, int _id=0) 
    : name(_name), data(_data), id(_id) {}
  string name;
  int id; // some identifier used when matching
  T data;
};

template <typename T>
struct Resource {
  typedef std::vector<ResourceEntry<T> > Type;
};

typedef ResourceEntry<TTF_Font*> FontEntry;
typedef ResourceEntry<game::Card*> CardEntry;
typedef Resource<TTF_Font*>::Type FontResource;
typedef Resource<game::Card*>::Type CardResource;

static FontResource fontResources;
static CardResource cardResources;

template <typename T>
T getResourceByName(const string& name, int id,
                    const typename Resource<T>::Type& resource) {
  typename Resource<T>::Type::const_iterator it;
  for (it = resource.begin(); it != resource.end(); ++it) {
    if (it->name == name && it->id == id) {
      return it->data;
    }
  }
  return 0;
}

TTF_Font* GetFont(const string& name, int ptSize) {
  TTF_Font* font;
  font = getResourceByName<TTF_Font*>(name, ptSize, fontResources);
  if (font) return font;

  font = font::Load(name, ptSize);
  FontEntry key(name, font, ptSize);
  fontResources.push_back(key);

  return font;
}

void AddCard(game::Card* card) {
  CardEntry entry(card->GetName(), card);
  cardResources.push_back(entry);
}

game::Card* GetCard(const string& name) {
  game::Card* card;
  card = getResourceByName<game::Card*>(name, 0, cardResources);
  if (card) return card;
  return NULL;
}


} // namespace resource
} // namespace dminion
