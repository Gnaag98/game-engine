#include "Vec2.h"

#include <cmath>
#include <utility>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "Vec3.h"

auto Vec2f::right(const float scalar) -> Vec2f {
  return Vec2f{ scalar, 0 };
}

auto Vec2f::up(const float scalar) -> Vec2f {
  return Vec2f{ 0, scalar };
}

Vec2f::Vec2f()
  : x{ 0.0f }, y{ 0.0f } {}
Vec2f::Vec2f(const float scalar)
  : x{ scalar }, y{ scalar } {}
Vec2f::Vec2f(const float _x, const float _y)
  : x{ _x }, y{ _y } {}
Vec2f::Vec2f(const Vec3f& other)
  : x{ other.x }, y{ other.y } {}

auto Vec2f::operator[](const int i) const -> const float& {
  return (&x)[i];
}

auto Vec2f::operator[](const int i) -> float& {
  return (&x)[i];
}

auto Vec2f::magnitude() const -> float {
  return std::sqrt(x * x + y * y);
}

auto Vec2f::dot(const Vec2f& other) const -> float {
  return x * other.x + y * other.y;
}

auto Vec2f::normalize() -> Vec2f& {
  auto magnitude_squared = dot(*this);

  // The square of a magnitude can't be negative.
  assert(magnitude_squared >= 0);

  if (magnitude_squared > 0) {
    auto inv_magnitude = 1.0f / std::sqrt(magnitude_squared);
    x *= inv_magnitude, y *= inv_magnitude;
  }

  return *this;
}

auto Vec2f::operator+=(const Vec2f& other) -> Vec2f& {
  x += other.x, y += other.y;
  return *this;
}

auto Vec2f::operator-=(const Vec2f& other) -> Vec2f& {
  x -= other.x, y -= other.y;
  return *this;
}

auto Vec2f::operator*=(const float scalar) -> Vec2f& {
  x *= scalar, y *= scalar;
  return *this;
}

auto Vec2f::operator/=(const float scalar) -> Vec2f& {
  x /= scalar, y /= scalar;
  return *this;
}

auto operator<<(std::ostream& s, const Vec2f& v) -> std::ostream& {
  auto old_flags = s.flags();
  auto width = 8;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "(" << std::setw(width) << v[0] <<
       ", " << std::setw(width) << v[1] << ")";

  s.flags(old_flags);
  return s;
}

auto operator+(Vec2f lhs, const Vec2f& rhs) -> Vec2f {
  return std::move(lhs += rhs);
}

auto operator-(Vec2f lhs, const Vec2f& rhs) -> Vec2f {
  return std::move(lhs -= rhs);
}

auto operator-(Vec2f vector) -> Vec2f {
  vector.x = -vector.x, vector.y = -vector.y;
  return vector;
}

auto operator*(Vec2f vector, const float scalar) -> Vec2f {
  return std::move(vector *= scalar);
}

auto operator*(const float scalar, Vec2f vector) -> Vec2f {
  return std::move(vector *= scalar);
}

auto operator/(Vec2f vector, const float scalar) -> Vec2f {
  return std::move(vector /= scalar);
}



Vec2i::Vec2i() : x{ 0 }, y{ 0 } {}
Vec2i::Vec2i(const int scalar) : x{ scalar }, y{ scalar } {}
Vec2i::Vec2i(const int _x, const int _y) : x{ _x }, y{ _y } {}

auto Vec2i::operator[](const int i) const -> const int& {
  return (&x)[i];
}

auto Vec2i::operator[](const int i) -> int& {
  return (&x)[i];
}

auto operator<<(std::ostream& s, const Vec2i& v) -> std::ostream& {
  auto old_flags = s.flags();
  auto width = 8;
  s.setf(std::ios_base::fixed);

  s << "(" << std::setw(width) << v[0] <<
       ", " << std::setw(width) << v[1] << ")";

  s.flags(old_flags);
  return s;
}