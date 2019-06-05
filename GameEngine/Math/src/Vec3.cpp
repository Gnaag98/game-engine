#include "Vec3.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include <cassert>

#include "Matrix44.h"

Vec3f::Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3f::Vec3f(float scalar) : x(scalar), y(scalar), z(scalar) {}
Vec3f::Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

const float& Vec3f::operator[](int i) const {
  return (&x)[i];
}

float& Vec3f::operator[](int i) {
  return (&x)[i];
}

Vec3f& Vec3f::operator+=(const Vec3f& other) {
  x += other.x, y += other.y, z += other.z;
  return *this;
}

Vec3f& Vec3f::operator-=(const Vec3f& other) {
  x -= other.x, y -= other.y, z -= other.z;
  return *this;
}

Vec3f& Vec3f::operator*=(const float scalar){
  x *= scalar, y *= scalar, z *= scalar;
  return *this;
}

Vec3f& Vec3f::operator/=(const float scalar) {
  x /= scalar, y /= scalar, z /= scalar;
  return *this;
}

//Vec3f Vec3f::operator+(const Vec3f& other) const {
//  return Vec3f(x + other.x, y + other.y, z + other.z);
//}
//
//Vec3f Vec3f::operator-(const Vec3f& other) const {
//  return Vec3f(x - other.x, y - other.y, z - other.z);
//}
//
//Vec3f Vec3f::operator*(const float scalar) const {
//  return Vec3f(x * scalar, y * scalar, z * scalar);
//}
//
//Vec3f Vec3f::operator/(const float scalar) const {
//  return Vec3f(x / scalar, y / scalar, z / scalar);
//}

//Vec3f Vec3f::operator*(const Matrix44f& m) const {
//  float a, b, c, w;
//
//  a = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
//  b = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
//  c = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
//  w = x * m[0][3] + y * m[1][3] + z * m[2][3] + m[3][3];
//
//  if (w != 1.0f && w != 0.0f) {
//    a /= w;
//    b /= w;
//    c /= w;
//  }
//
//  return Vec3f(a, b, c);
//}

Vec3f& Vec3f::operator*=(const Matrix44f& m) {
  float result_x, result_y, result_z, result_w;

  result_x = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
  result_y = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
  result_z = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
  result_w = x * m[0][3] + y * m[1][3] + z * m[2][3] + m[3][3];

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

float Vec3f::magnitude() const {
  return std::sqrt(x * x + y * y + z * z);
}

float Vec3f::dot(const Vec3f& other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vec3f& Vec3f::normalize() {
  float magnitude_squared = dot(*this);
  
  // The square of a magnitude can't be negative.
  assert(magnitude_squared >= 0);
  
  if (magnitude_squared > 0) {
    float inv_magnitude = 1 / std::sqrt(magnitude_squared);
    x *= inv_magnitude, y *= inv_magnitude, z *= inv_magnitude;
  }
  
  return *this;
}

// Linear interpolation given two vectors.
// Allows percent to be negative and |percent| > 1.
Vec3f& Vec3f::lerp(const Vec3f& start, const Vec3f& end, const float percent) {
  if (start == end)
    *this = start;
  else
    *this = start + (end - start) * percent;

  return *this;
}

std::ostream& operator<<(std::ostream& s, const Vec3f& v) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 8;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "( " << std::setw(width) << v[0] <<
       ", " << std::setw(width) << v[1] <<
       ", " << std::setw(width) << v[2] << " )";

  s.flags(old_flags);
  return s;
}

Vec3f operator+(Vec3f lhs, const Vec3f & rhs) {
  return std::move(lhs += rhs);
}

Vec3f operator-(Vec3f lhs, const Vec3f & rhs) {
  return std::move(lhs -= rhs);
}

Vec3f operator-(Vec3f vector) {
  vector.x = -vector.x, vector.y = -vector.y, vector.z = -vector.z;
  return vector;
}

Vec3f operator*(Vec3f lhs, const float scalar) {
  return std::move(lhs *= scalar);
}

Vec3f operator*(const float scalar, Vec3f rhs) {
  return std::move(rhs *= scalar);
}

Vec3f operator/(Vec3f lhs, const float scalar) {
  return std::move(lhs /= scalar);
}

Vec3f operator*(Vec3f vector, const Matrix44f & matrix) {
  return std::move(vector *= matrix);
}

bool operator==(const Vec3f& lhs, const Vec3f& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vec3f& lhs, const Vec3f& rhs) {
  return !(lhs == rhs);
}
