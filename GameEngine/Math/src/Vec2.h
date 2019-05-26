#pragma once

#include <ostream>

#include "Vec3.h"

class Vec2f {
public:
  float x, y;

  Vec2f();
  Vec2f(float scalar);
  Vec2f(float x, float y);
  Vec2f(const Vec3f& other);

  //  Access operators.
  const float& operator[](int i) const;
  float& operator[](int i);

  Vec2f operator+(const Vec2f& other) const;
  Vec2f operator-(const Vec2f& other) const;

  Vec2f operator*(const float scalar) const;
  Vec2f operator/(const float scalar) const;

  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Vec2f& m);
};

class Vec2i {
public:
  int x, y;

  Vec2i();
  Vec2i(int scalar);
  Vec2i(int x, int y);

  //  Access operators.
  const int& operator[](int i) const;
  int& operator[](int i);

  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Vec2i& m);
};