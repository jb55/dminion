#ifndef _DMINION_RESOURCE_
#define _DMINION_RESOURCE_
#include "common.h"
#include "card.h"
#include "SDL/SDL_ttf.h"
#include <map>

namespace dminion {
namespace resource {

template <typename K, typename V, typename D, typename K2=int>
class Manager
{
protected:
  struct ResourceKey {
    ResourceKey(const K& _key, K2 _id=K2()) : key(_key), id(_id) {}
    K key;
    K2 id; // some identifier used when matching

    bool operator<(const ResourceKey& rhs) const {
      return key < rhs.key;
    }
  };

  typedef ResourceKey key_type;
  typedef std::map<key_type, V> storage_type;

  storage_type resources;

public:

  V Load(const K& key1, const K2& key2) {
    return V();
  }

  V Get(const K& key, const K2& id=K2()) {
    typename storage_type::const_iterator it;
    for (it = resources.begin(); it != resources.end(); ++it) {
      if (it->first.key == key && it->first.id == id) {
        return it->second;
      }
    }

    // static polymorphism ftw!
    V val = static_cast<D*>(this)->Load(key, id);
    Add(key, val, id);
    return val;
  }

  void Add(const K& key, const V& val, const K2& key2=K2()) {
    key_type newKey(key, key2);
    resources[newKey] = val;
  }
};

class TextureManager : public Manager<string, Texture, TextureManager>
{
public:
  Texture Load(const string& key, const int& unused=0);
};

class CardTextureManager : 
      public Manager<Card*, Texture, CardTextureManager>
{
public:
  Texture Load(Card* const& card, const int& unused=0);
};

class CardManager : public Manager<string, Card*, CardManager>
{
public:
  Card* Load(const string& key, const int& unused);
};

class FontManager : public Manager<string, TTF_Font*, FontManager>
{
public:
  TTF_Font* Load(const string& key, const int& ptSize);
};

TTF_Font* GetFont(const string& name, int ptSize);
Texture GetTexture(const string& name);
Texture GetCardTexture(Card* card);
Card* GetCard(const string& name);
void AddCard(Card* card);

} // namespace resource
} // namespace dminion

#endif // _DMINION_RESOURCE_
