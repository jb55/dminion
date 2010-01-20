#ifndef _DMINION_RESOURCE_
#define _DMINION_RESOURCE_
#include "types.h"
#include "SDL/SDL_ttf.h"
#include <map>

namespace dminion {
namespace game { class Card; }

namespace resource {

template <typename K, typename V, typename K2=int>
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

  virtual ~Manager() {}

  virtual V Load(const K&, const K2&) {
    return V();
  }

  V Get(const K& key, const K2& id=K2()) {
    typename storage_type::const_iterator it;
    for (it = resources.begin(); it != resources.end(); ++it) {
      if (it->first.key == key && it->first.id == id) {
        return it->second;
      }
    }

    return Load(key, id);
  }

  void Add(const K& key, const V& val, const K2& key2=K2()) {
    key_type newKey(key, key2);
    resources[newKey] = val;
  }
};

class TextureManager : public Manager<string, Texture>
{
public:
  Texture Load(const string& key, const int& unused=0);
};

class CardTextureManager : public Manager<game::Card*, Texture>
{
public:
  Texture Load(const game::Card*& card, const int& unused=0);
};

class CardManager : public Manager<string, game::Card*, string>
{
public:
  game::Card* Load(const string& key, const string& set);
};

class FontManager : public Manager<string, TTF_Font*>
{
public:
  TTF_Font* Load(const string& key, const int& ptSize);
};

TTF_Font* GetFont(const string& name, int ptSize);
Texture GetTexture(const string& name);
Texture GetCardTexture(game::Card* card);
game::Card* GetCard(const string& name);
void AddCard(game::Card* card);



} // namespace resource
} // namespace dminion

#endif // _DMINION_RESOURCE_
