#ifndef _DMINION_TYPES_H_
#define _DMINION_TYPES_H_

#if __STDC_VERSION__ >= 199901L
#include <stdint.h>
#else
typedef unsigned short uint16_t;
#endif

#include <string>
#include "GL/gl.h"

struct SDL_Surface;

namespace dminion {

typedef std::string string;
typedef SDL_Surface* Texture;

//
// Vec2
//
struct Vec2
{
  float x, y;

  Vec2(float _x, float _y) : x(_x), y(_y) {}

  Vec2& operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  const Vec2 operator+(const Vec2& other) const {
    return Vec2(*this) += other;
  }
};

//
// Color
//
struct Color
{
  char r, g, b, a;

  Color(char _r, char _g, char _b, char _a) : r(_r), g(_g), b(_b), a(_a) {}
  Color(char _r, char _g, char _b) : r(_r), g(_g), b(_b), a(255) {}
};

} // namespace dminion

#endif // _DMINION_TYPES_H_
