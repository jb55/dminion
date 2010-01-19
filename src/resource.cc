#include "resource.h"
#include "types.h"
#include "font.h"
#include "util.h"
#include "card.h"
#include "gamecard.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <vector>

namespace dminion {
namespace resource {

template <typename T>
struct ResourceEntry {
  ResourceEntry(const string& _name, T& _data, int _id=0) 
    : name(_name), data(_data), id(_id) {}
  string name;
  T data;
  int id; // some identifier used when matching
};

template <typename T>
struct Resource {
  typedef std::vector<ResourceEntry<T> > Type;
};

typedef ResourceEntry<TTF_Font*> FontEntry;
typedef ResourceEntry<game::Card*> CardEntry;
typedef ResourceEntry<SDL_Surface*> ImageEntry;
typedef Resource<TTF_Font*>::Type FontResource;
typedef Resource<game::Card*>::Type CardResource;
typedef Resource<SDL_Surface*>::Type ImageResource;

static FontResource fontResources;
static CardResource cardResources;
static ImageResource imageResources;

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

SDL_Surface* GetImage(const string& name) {
  SDL_Surface* image;
  SDL_Surface* optImage;
  image = getResourceByName<SDL_Surface*>(name, 0, imageResources);
  if (image) return image;

  image = IMG_Load(name.c_str());
  std::cout << IMG_GetError();
  flush(std::cout);
  optImage = SDL_DisplayFormatAlpha(image);
  SDL_FreeSurface(image);
  image = optImage;
  
  ImageEntry entry(name, image);
  imageResources.push_back(entry);

  return image;
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
