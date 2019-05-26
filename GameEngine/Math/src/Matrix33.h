#pragma once

#include <ostream>

#include "Matrix36.h"

class Matrix33f {
private:
  float m[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };

public:
  Matrix33f();
  Matrix33f(const Matrix33f& other);
  Matrix33f(float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i);
  //  Create a 2x2 matrix out of the right part of a 2x4 matrix. 
  Matrix33f(const Matrix36f& other);
  //  Copy assignment operator.
  Matrix33f& operator=(const Matrix33f& other);

  //  Access operators.
  const float* operator[](int i) const;
  float* operator[](int i);

  //  Determinant.
  float det() const;
  Matrix33f inverse() const;

public:
  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Matrix33f& m);
};