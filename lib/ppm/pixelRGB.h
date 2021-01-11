#ifndef PIXELRGB_H
#define PIXELRGB_H

#include "pixel.h"
#include <unordered_map>

// TODO: wyjebac for production
typedef unsigned char Color;

// klasa pixel rgb przechowywac bedzie kolory w formacie rgb
class pixelRGB {
public:
  pixelRGB(){}; //= delete;
  pixelRGB(Color r, Color g, Color b) : r(r), g(g), b(b) {}
  void set();
  virtual ~pixelRGB(){};
  virtual Color R() { return r; }
  virtual Color G() { return g; }
  virtual Color B() { return b; }
  operator const int() const { return (256 * 256 * r) + (256 * g) + b; }
  bool operator==(const pixelRGB &other) {
    return this->r == other.r && this->g == other.g && this->b == other.b;
  }

  // jezeli |X| to moc zbioru X i y = a|X|^2 + b|X| + c gdzie a,b,c \in X
  // to y jednoznacznie okresla punkt w 3-w przestrzeni kolorow
  inline unsigned hash() { return (256 * 256 * r) + (256 * g) + b; }

protected:
  Color r, g, b;
};

namespace std {

template <> struct hash<pixelRGB> {
  std::size_t operator()(const pixelRGB &pixel) const {
    return (const int)pixel;
  }
};

} // namespace std

#endif
