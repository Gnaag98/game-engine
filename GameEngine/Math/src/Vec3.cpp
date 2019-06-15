#include "Vec3.h"

#include <cmath>
#include <stdexcept>
#include <utility>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "Matrix44.h"

auto Vec3f::right(const float scalar) -> Vec3f {
  return Vec3f{ scalar, 0, 0 };
}

auto Vec3f::up(const float scalar) -> Vec3f {
  return Vec3f{ 0, scalar, 0 };
}

auto Vec3f::forward(const float scalar) -> Vec3f {
  return Vec3f{ 0, 0, scalar };
}

Vec3f::Vec3f()
  : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}
Vec3f::Vec3f(const float scalar)
  : x{ scalar }, y{ scalar }, z{ scalar } {}
Vec3f::Vec3f(const float _x, const float _y, const float _z)
  : x{ _x }, y{ _y }, z{ _z } {}

auto Vec3f::operator[](int i) const -> const float& {
  return (&x)[i];
}

auto Vec3f::operator[](int i) -> float& {
  return (&x)[i];
}

auto Vec3f::magnitude() const -> float {
  return std::sqrt(x * x + y * y + z * z);
}

auto Vec3f::dot(const Vec3f& other) const -> float {
  return x * other.x + y * other.y + z * other.z;
}

auto Vec3f::normalize() -> Vec3f& {
  auto magnitude_squared = dot(*this);
  
  // The square of a magnitude can't be negative.
  assert(magnitude_squared >= 0);
  
  if (magnitude_squared > 0) {
    auto inv_magnitude = 1.0f / std::sqrt(magnitude_squared);
    x *= inv_magnitude, y *= inv_magnitude, z *= inv_magnitude;
  }
  
  return *this;
}

auto Vec3f::lerp(const Vec3f& start, const Vec3f& end, const float percent) -> Vec3f& {
  if (start == end)
    *this = start;
  else
    *this = start + (end - start) * percent;

  return *this;
}

auto Vec3f::operator+=(const Vec3f& other) -> Vec3f& {
  x += other.x, y += other.y, z += other.z;
  return *this;
}

auto Vec3f::operator-=(const Vec3f& other) -> Vec3f& {
  x -= other.x, y -= other.y, z -= other.z;
  return *this;
}

auto Vec3f::operator*=(const float scalar) -> Vec3f& {
  x *= scalar, y *= scalar, z *= scalar;
  return *this;
}

auto Vec3f::operator/=(const float scalar) -> Vec3f& {
  x /= scalar, y /= scalar, z /= scalar;
  return *this;
}

auto Vec3f::operator*=(const Matrix44f& m) -> Vec3f& {
  auto result_x = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
  auto result_y = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
  auto result_z = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
  auto result_w = x * m[0][3] + y * m[1][3] + z * m[2][3] + m[3][3];

  // TODO: Err of w == 0.
  if (!(result_w == 1 || result_w == 0)) {
    result_x /= result_w;
    result_y /= result_w;
    result_z /= result_w;
  }
  x = result_x, y = result_y, z = result_z;
  return *this;
}

Vec3f::operator bool() const {
  return x || y || z;
}

auto operator<<(std::ostream& s, const Vec3f& v) -> std::ostream& {
  auto old_flags = s.flags();
  auto width = 8;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "( " << std::setw(width) << v[0] <<
       ", " << std::setw(width) << v[1] <<
       ", " << std::setw(width) << v[2] << " )";

  s.flags(old_flags);
  return s;
}

auto operator+(Vec3f lhs, const Vec3f & rhs) -> Vec3f {
  return std::move(lhs += rhs);
}

auto operator-(Vec3f lhs, const Vec3f & rhs) -> Vec3f {
  return std::move(lhs -= rhs);
}

auto operator-(Vec3f vector) -> Vec3f {
  vector.x = -vector.x, vector.y = -vector.y, vector.z = -vector.z;
  return vector;
}

auto operator*(Vec3f vector, const float scalar) -> Vec3f {
  return std::move(vector *= scalar);
}

auto operator*(const float scalar, Vec3f vector) -> Vec3f {
  return std::move(vector *= scalar);
}

auto operator/(Vec3f vector, const float scalar) -> Vec3f {
  return std::move(vector /= scalar);
}

auto operator*(Vec3f vector, const Matrix44f& matrix) -> Vec3f {
  return std::move(vector *= matrix);
}

auto operator==(const Vec3f& lhs, const Vec3f& rhs) -> bool {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

auto operator!=(const Vec3f& lhs, const Vec3f& rhs) -> bool {
  return !(lhs == rhs);
}
