#pragma once

#include <ostream>

#include "Matrix24.h"

class Matrix22f {
private:
  float m[2][2] = {
    {1, 0},
    {0, 1}
  };

public:
  Matrix22f();
  Matrix22f(const Matrix22f& other);
  Matrix22f(float a, float b,
            float c, float d);
  //  Create a 2x2 matrix out of the right part of a 2x4 matrix. 
  Matrix22f(const Matrix24f& other);
  //  Copy assignment operator.
  Matrix22f& operator=(const Matrix22f& other);

  //  Access operators.
  const float* operator[](int i) const;
  float* operator[](int i);

  //  Determinant.
  float det() const;
  Matrix22f inverse() const;

  /*  TODO:
   *
   *  Transpose.
   *  Multiplication.
  */
public:
  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Matrix22f& m);
};