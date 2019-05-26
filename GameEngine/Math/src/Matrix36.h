#pragma once

#include <ostream>

class Matrix33f;

//  Used when finding the inverse of a 3x3 matrix.
class Matrix36f {
private:
  float m[3][6] = {
    {1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 1}
  };

public:
  Matrix36f();
  //  Inserts 3x3 matrix into left half of matrix. 
  Matrix36f(const Matrix33f& other);

  //  Access operators.
  const float* operator[](int i) const;
  float* operator[](int i);

  //  Reduced Row Echelon Form using Gaussian - Jordan elimination.
  Matrix36f& rref();

private:
  void swap_rows(float row_a[6], float row_b[6]);
  void multiply_row(float row[6], float value);
  void add_rows(float row_a[6], float row_b[6]);

public:
  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Matrix36f& m);
};