#pragma once

#include <ostream>

class Matrix44f;

//  Used when finding the inverse of a 3x3 matrix.
class Matrix48f {
private:
  float m[4][8] = {
    {1, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 1}
  };

public:
  Matrix48f();
  //  Inserts 3x3 matrix into left half of matrix. 
  Matrix48f(const Matrix44f& other);

  //  Access operators.
  const float* operator[](int i) const;
  float* operator[](int i);

  //  Reduced Row Echelon Form using Gaussian - Jordan elimination.
  Matrix48f& rref();

private:
  void swap_rows(float row_a[8], float row_b[8]);
  void multiply_row(float row[8], float value);
  void add_rows(float row_a[8], float row_b[8]);

public:
  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Matrix48f& m);
};