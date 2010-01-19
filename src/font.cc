#include "font.h"
#include "util.h"
#include <iostream>

namespace dminion {
namespace font {

TTF_Font* Load(const string& file, int ptSize) {
  TTF_Font* tmpFont;
  tmpFont = TTF_OpenFont(file.c_str(), ptSize);
  if (tmpFont == NULL) {
    std::cout << "Unable to load font: " 
              << file << " " << TTF_GetError() << std::endl;
  }

  return tmpFont;
}

SDL_Surface* DrawTextToSurface(TTF_Font* font, const Color& fgColor,
                               const Color& bgColor, const string& text,
                               FontQuality quality) {
  SDL_Color fontColor;
  SDL_Color fontBgColor;
  SDL_Surface* resultText;

  util::ColorToSDL(fgColor, &fontColor);
  util::ColorToSDL(bgColor, &fontBgColor);

  switch (quality) {
  default:
  case kSolid:
    resultText = TTF_RenderUTF8_Solid(font, text.c_str(), fontColor);
    break;
  case kShaded:
    resultText = TTF_RenderUTF8_Shaded(font, text.c_str(), fontColor, fontBgColor);
    break;
  case kBlended:
    resultText = TTF_RenderUTF8_Blended(font, text.c_str(), fontColor);
    break;
  }

  return resultText;
}

} // namespace font
} // namespace dminion
