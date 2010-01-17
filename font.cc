#include "font.h"
#include <iostream>

namespace dminion {
namespace util {

TTF_Font* LoadFont(const char* file, int ptSize) {
  TTF_Font* tmpFont;
  tmpFont = TTF_OpenFont(file, ptSize);
  if (tmpFont == NULL) {
    std::wcout << L"Unable to load font: " 
               << file << L" " << TTF_GetError() << std::endl;
  }
  return tmpFont;
}

}
}
