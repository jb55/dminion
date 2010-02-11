#ifndef _DMINION_DENSEPAIR_H_
#define _DMINION_DENSEPAIR_H_

namespace dminion {

template <typename F, typename S>
class DensePair
{
  uint16_t f;
  uint16_t s;

  void packFirst(F first) {
    f = static_cast<uint16_t>(first);
  }

  void packSecond(S second) {
    s = static_cast<uint16_t>(second);
  }

public:

  DensePair() {}

  DensePair(F first, S second) : f(0), s(0) {
    packFirst(first);
    packSecond(second);
  }

  F first() {
    return static_cast<F>(f);
  }

  S second() {
    return static_cast<S>(s);
  }
};

} // namespace dminion

#endif // _DMINION_DENSEPAIR_H_
