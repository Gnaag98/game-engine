#pragma once

#include <ostream>

class Matrix44f;

class Vec3f {
public:
  static auto right(const float scalar = 1) -> Vec3f;
  static auto up(const float scalar = 1) -> Vec3f;
  static auto forward(const float scalar = 1) -> Vec3f;

public:
  float x, y, z;

public:
  Vec3f();
  explicit Vec3f(const float scalar);
  Vec3f(const float x, const float y, const float z);

  auto operator[](const int i) const -> const float&;
  auto operator[](const int i) -> float&;

  auto magnitude() const -> float;
  auto dot(const Vec3f& other) const -> float;

  auto normalize() -> Vec3f&;

  // Linear interpolation given two vectors.
  // Allows percent to be negative and |percent| > 1.
  auto lerp(const Vec3f& start, const Vec3f& end, float percent) -> Vec3f&;

  auto operator+=(const Vec3f& other) -> Vec3f&;
  auto operator-=(const Vec3f& other) -> Vec3f&;
  auto operator*=(const float scalar) -> Vec3f&;
  auto operator/=(const float scalar) -> Vec3f&;

  auto operator*=(const Matrix44f& matrix) -> Vec3f&;

  explicit operator bool() const;

  friend auto operator<<(std::ostream& ostream, const Vec3f& vector) -> std::ostream&;
};

auto operator+(Vec3f lhs, const Vec3f& rhs) -> Vec3f;
auto operator-(Vec3f lhs, const Vec3f& rhs) -> Vec3f;
auto operator-(Vec3f vector) -> Vec3f;
auto operator*(Vec3f vector, const float scalar) -> Vec3f;
auto operator*(const float scalar, Vec3f vector) -> Vec3f;
auto operator/(Vec3f vector, const float scalar) -> Vec3f;

auto operator*(Vec3f vector, const Matrix44f& matrix) -> Vec3f;

auto operator==(const Vec3f& lhs, const Vec3f& rhs) -> bool;
auto operator!=(const Vec3f& lhs, const Vec3f& rhs) -> bool;
