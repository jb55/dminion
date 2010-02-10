#include "font.h"
#include "util.h"
#include <iostream>

namespace dminion {
namespace font {

const string kDefaultFontDir = "/usr/share/fonts/truetype/freefont/";
const string kDefaultFont = "FreeSerif.ttf";
const string kDescFont = "FreeSans.ttf";

const string& GetDefault() {
  static const string kDefault = kDefaultFontDir + kDefaultFont;
  return kDefault;
}

const string& GetSans() {
  static const string kDesc = kDefaultFontDir + kDescFont;
  return GetDefault();
}

TTF_Font* Load(const string& file, int ptSize) {
  TTF_Font* tmpFont;
  tmpFont = TTF_OpenFont(file.c_str(), ptSize);
  if (tmpFont == NULL) {
    std::cout << "Unable to load font: " 
              << file << " " << TTF_GetError() << std::endl;
  }

  return tmpFont;
}

} // namespace font
} // namespace dminion
