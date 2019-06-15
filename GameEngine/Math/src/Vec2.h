#pragma once

#include <ostream>

#include "Vec3.h"

class Vec2f {
public:
  static auto right(const float scalar = 1) -> Vec2f;
  static auto up(const float scalar = 1) -> Vec2f;

public:
  float x, y;

  Vec2f();
  explicit Vec2f(const float scalar);
  Vec2f(const float x, const float y);
  Vec2f(const Vec3f& other);

  auto operator[](const int i) const -> const float&;
  auto operator[](const int i) -> float&;

  auto magnitude() const -> float;
  auto dot(const Vec2f& other) const -> float;

  auto normalize()->Vec2f&;

  auto operator+=(const Vec2f& other) -> Vec2f&;
  auto operator-=(const Vec2f& other) -> Vec2f&;
  auto operator*=(const float scalar) -> Vec2f&;
  auto operator/=(const float scalar) -> Vec2f&;

  friend auto operator<<(std::ostream& ostream, const Vec2f& matrix) -> std::ostream&;
};

auto operator+(Vec2f lhs, const Vec2f& rhs) -> Vec2f;
auto operator-(Vec2f lhs, const Vec2f& rhs) -> Vec2f;
auto operator-(Vec2f vector) -> Vec2f;
auto operator*(Vec2f vector, const float scalar) -> Vec2f;
auto operator*(const float scalar, Vec2f vector) -> Vec2f;
auto operator/(Vec2f vector, const float scalar) -> Vec2f;

class Vec2i {
public:
  int x, y;

  Vec2i();
  Vec2i(const int scalar);
  Vec2i(const int x, const int y);

  auto operator[](const int i) const -> const int&;
  auto operator[](const int i) -> int&;

  friend auto operator<<(std::ostream& ostream, const Vec2i& matrix) -> std::ostream&;
};