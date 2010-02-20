#include "font.h"
#include "util.h"
#include "log.h"
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
    ERROR2("Unable to load font: %s %s", file % TTF_GetError());
  }

  return tmpFont;
}

} // namespace font
} // namespace dminion
