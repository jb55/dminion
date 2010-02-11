#include <stdlib.h>
#include <sstream>
#include <vector>
#include "util.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "types.h" 
#include "gamecard.h" 
#include "card.h" 

namespace dminion {
namespace util {

SDL_Surface* LoadImage(const string& filename) {
  SDL_Surface* surface, *optSurface;
  surface = IMG_Load(filename.c_str());
  if (!surface) {
    return 0;
  }
  bool hasAlpha = false;

  // Does the texture contain an alpha channel?
  SDL_PixelFormat* fmt = surface->format;
  hasAlpha = fmt->Amask && fmt->Ashift; 

  optSurface = hasAlpha ? SDL_DisplayFormatAlpha(surface) :
                          SDL_DisplayFormat(surface);

  SDL_FreeSurface(surface);
  return optSurface;
}

Texture SurfaceToTexture(SDL_Surface* surface, bool needsBase) {
  const int w = surface->w;
  const int h = surface->w;

  SDL_Surface* image;

  if (needsBase) {
    SDL_PixelFormat* fmt = surface->format;
    image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
                                 fmt->Bmask, fmt->Gmask,
                                 fmt->Rmask, fmt->Amask);
    SDL_BlitSurface(surface, NULL, image, NULL);
  } else {
    image = surface;
  }

  /*
  GLuint id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image->pixels);

  SDL_FreeSurface(image);
  */
  return image;
}

void FormatStats(int* bonus, StatList& stats) {
  for (int i = 0; i < game::kNumBonuses; ++i) {
    int b = bonus[i];
    int icon = game::kNumBonuses;
    if (b == 0) continue;
    std::stringstream os;
    os << (b < 0 ? "- " : "+ ") << b << " ";

    if (b == game::kCardBonus || b == game::kActionBonus) {
      os << card::GetBonusString(i);
      if (abs(b) > 1) os << "s";
    }
    else {
      icon = b;
    }

    stats.push_back(Stat(os.str(), icon));
  }
}

bool FormatDescription(const string& description, std::vector<string>& lines,
                       size_t breakSize) {
  typedef string::const_iterator iter_type; 
  size_t dSize = description.size();

  if (dSize <= breakSize) {
    return false;
  }

  iter_type first = description.begin();
  iter_type last;

  for (size_t i = 0, x = 0; i < dSize; ++i, ++x) {
    char c = description.at(i);
    if ((i == dSize - 1) || (x > breakSize && c == ' ')) {
      string newStr(x, '\0');
      last = first + x;
      std::copy(first, last, newStr.begin());
      lines.push_back(newStr);

      first = description.begin() + i;
      x = 0;
    }
  }

  return true;
}

TextureSize DrawTextToSurface(SDL_Surface* dstSurface,
                       const Vec2& pos,
                       TTF_Font* font,
                       const string& text,
                       font::Alignment align,
                       const Color& fgColor,
                       const Color& bgColor,
                       font::Quality quality) {
  SDL_Color fontColor;
  SDL_Color fontBgColor;
  SDL_Rect dstRect;
  SDL_Surface* resultText;
  int width = 0;
  int height = 0;

  util::ColorToSDL(fgColor, &fontColor);
  util::ColorToSDL(bgColor, &fontBgColor);

  switch (quality) {
  default:
  case font::kSolid:
    resultText = TTF_RenderUTF8_Solid(font, text.c_str(), fontColor);
    break;
  case font::kShaded:
    resultText = TTF_RenderUTF8_Shaded(font, text.c_str(), fontColor, 
                                       fontBgColor);
    break;
  case font::kBlended:
    resultText = TTF_RenderUTF8_Blended(font, text.c_str(), fontColor);
    break;
  }

  width = resultText->w;
  height = resultText->h;
  util::PositionSurface(resultText, pos, dstRect, dstSurface, align);

  SDL_BlitSurface(resultText, NULL, dstSurface, &dstRect);
  SDL_FreeSurface(resultText);

  return TextureSize(width, height);
}

void ColorToSDL(const Color& color, SDL_Color* sdlColor) {
  sdlColor->r = color.r;
  sdlColor->g = color.g;
  sdlColor->b = color.b;
}

void PositionSurface(SDL_Surface* surface, const Vec2& pos, SDL_Rect& rect, 
                     SDL_Surface* dstSurface, font::Alignment align) {
  short x, y;
  if (align == font::kCenter) {
    x = static_cast<short>((static_cast<float>(dstSurface->w) / 2.0) - 
                           (static_cast<float>(surface->w) / 2.0)) + pos.x;
  } else {
    x = static_cast<short>(pos.x);
  }

  y = static_cast<short>(pos.y);
  rect.x = x;
  rect.y = y;
  rect.w = surface->w;
  rect.h = surface->h;
}

// Counts the number of bits set in flags
unsigned int CountBitsSet(unsigned int flags) {
  unsigned int count;
  for (count = 0; flags; count++) {
    flags &= flags - 1;
  }
  return count;
}

uint16_t* WideToU16(const wchar_t* wide, 
                    uint16_t* u16, 
                    size_t size) {
  if (sizeof(wchar_t) == sizeof(uint16_t)) {
    return reinterpret_cast<uint16_t*>(const_cast<wchar_t*>(wide));
  }

  for (size_t i = 0; i < size; ++i) {
    u16[i] = static_cast<uint16_t>(wide[i]);
  }

  u16[size] = '\0';
  return u16;
}

char* WideToChar(const wchar_t* wide, char* ch, size_t size) {
  wcstombs(ch, wide, size);
  ch[size] = '\0';
  return ch;
}

} // namespace util
} // namespace dminion
