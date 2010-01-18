#include "font.h"
#include "util.h"
#include <iostream>

namespace dminion {
namespace font {

TTF_Font* Load(const string& file, int ptSize) {
  TTF_Font* tmpFont;
  const size_t size = file.size();
  char* cFile = new char[size+1];
  cFile = util::WideToChar(file.c_str(), cFile, size);

  tmpFont = TTF_OpenFont(cFile, ptSize);
  if (tmpFont == NULL) {
    std::wcout << L"Unable to load font: " 
               << file << L" " << TTF_GetError() << std::endl;
  }

  delete[] cFile;
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

  size_t size = text.size();
  uint16_t* shortBuf = new uint16_t[size+1];
  uint16_t* u16Text;
  u16Text = util::WideToU16(text.c_str(), shortBuf, size);

  switch (quality) {
  default:
  case kSolid:
    resultText = TTF_RenderUNICODE_Solid(font, u16Text, fontColor);
    break;
  case kShaded:
    resultText = TTF_RenderUNICODE_Shaded(font, u16Text, fontColor, fontBgColor);
    break;
  case kBlended:
    resultText = TTF_RenderUNICODE_Blended(font, u16Text, fontColor);
    break;
  }

  delete[] shortBuf;

  return resultText;
}

} // namespace font
} // namespace dminion
