#pragma once

#include <ostream>

#include "Matrix48.h"

class Matrix44f {
private:
  float m[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };

public:
  explicit Matrix44f(bool is_unit_matrix = true);
  Matrix44f(const Matrix44f& other);
  Matrix44f(float a, float b, float c, float d,
            float e, float f, float g, float h,
            float i, float j, float k, float l,
            float n, float o, float p, float q);
  //  Create a 2x2 matrix out of the right part of a 2x4 matrix. 
  Matrix44f(const Matrix48f& other);
  //  Copy assignment operator.
  Matrix44f& operator=(const Matrix44f& other);

  //  Access operators.
  const float* operator[](int i) const;
  float* operator[](int i);

  //  Determinant.
  float det() const;
  Matrix44f inverse() const;

  //  Multiplication.
  Matrix44f operator*(const Matrix44f& other) const;
  Matrix44f& operator*=(const Matrix44f& other);

  //  Transformations.
  static Matrix44f scalar(float scale);
  static Matrix44f scalar(float x, float y, float z);
  static Matrix44f rotation_x(float angle);
  static Matrix44f rotation_y(float angle);
  static Matrix44f rotation_z(float angle);
  static Matrix44f translation(float x, float y, float z);
  Matrix44f& scale(float scalar);
  Matrix44f& scale(float x, float y, float z);
  Matrix44f& rotate_x(float angle);
  Matrix44f& rotate_y(float angle);
  Matrix44f& rotate_z(float angle);
  Matrix44f& translate(float x, float y, float z);

public:
  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Matrix44f& m);
};