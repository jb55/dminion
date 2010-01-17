#ifndef _DMINION_TYPES_H_
#define _DMINION_TYPES_H_

#include <string>

namespace dminion {

typedef std::wstring string;

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

}

#endif // _DMINION_TYPES_H_
