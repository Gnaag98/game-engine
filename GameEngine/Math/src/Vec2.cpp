#include "Vec2.h"

#include <iostream>
#include <iomanip>

#include "Vec3.h"

Vec2f::Vec2f() : x(0.0f), y(0.0f) {}
Vec2f::Vec2f(float scalar) : x(scalar), y(scalar) {}
Vec2f::Vec2f(float _x, float _y) : x(_x), y(_y) {}
Vec2f::Vec2f(const Vec3f& other) : x(other.x), y(other.y) {}

const float& Vec2f::operator[](int i) const {
  return (&x)[i];
}

float& Vec2f::operator[](int i) {
  return (&x)[i];
}

Vec2f Vec2f::operator+(const Vec2f& other) const {
  return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator-(const Vec2f& other) const {
  return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator*(const float scalar) const {
  return Vec2f(x * scalar, y * scalar);
}

Vec2f Vec2f::operator/(const float scalar) const {
  return Vec2f(x / scalar, y / scalar);
}

std::ostream& operator<<(std::ostream& s, const Vec2f& v) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 8;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "(" << std::setw(width) << v[0] <<
    ", " << std::setw(width) << v[1] << ")";

  s.flags(old_flags);
  return s;
}



Vec2i::Vec2i() : x(0), y(0) {}
Vec2i::Vec2i(int scalar) : x(scalar), y(scalar) {}
Vec2i::Vec2i(int _x, int _y) : x(_x), y(_y) {}

const int& Vec2i::operator[](int i) const {
  return (&x)[i];
}

int& Vec2i::operator[](int i) {
  return (&x)[i];
}

std::ostream& operator<<(std::ostream& s, const Vec2i& v) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 8;
  s.setf(std::ios_base::fixed);

  s << "( " << std::setw(width) << v[0] <<
       ", " << std::setw(width) << v[1] << " )";

  s.flags(old_flags);
  return s;
}