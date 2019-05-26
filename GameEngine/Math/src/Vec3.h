#pragma once

#include <cmath>
#include <ostream>

#include "Matrix44.h"

class Vec3f {
public:
  float x, y, z;

public:
  Vec3f();
  explicit Vec3f(float scalar);
  Vec3f(float x, float y, float z);

  //  Access operators.
  const float& operator[](int i) const;
  float& operator[](int i);

  Vec3f& operator+=(const Vec3f& other);
  Vec3f& operator-=(const Vec3f& other);
  Vec3f& operator*=(const float scalar);
  Vec3f& operator/=(const float scalar);

  Vec3f& operator*=(const Matrix44f& matrix);

  explicit operator bool() const;
  
  float magnitude() const;
  float dot(const Vec3f& other) const;

  Vec3f& normalize();
  
  Vec3f& lerp(const Vec3f& start, const Vec3f& end, float percent);

  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& stream, const Vec3f& vector);
};

Vec3f operator+(Vec3f lhs, const Vec3f& rhs);
Vec3f operator-(Vec3f lhs, const Vec3f& rhs);
Vec3f operator-(Vec3f vector);
Vec3f operator*(Vec3f lhs, const float scalar);
Vec3f operator*(const float scalar, Vec3f rhs);
Vec3f operator/(Vec3f lhs, const float scalar);

Vec3f operator*(Vec3f vector, const Matrix44f& matrix);

bool operator==(const Vec3f& lhs, const Vec3f& rhs);
bool operator!=(const Vec3f& lhs, const Vec3f& rhs);