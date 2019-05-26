#pragma once

#include <ostream>

class Matrix22f;

//  Used when finding the inverse of a 2x2 matrix.
class Matrix24f {
private:
  float m[2][4] = {
    {1, 0, 1, 0},
    {0, 1, 0, 1}
  };

public:
  Matrix24f();
  //  Inserts 2x2 matrix into left half of matrix. 
  Matrix24f(const Matrix22f& other);

  //  Access operators.
  const float* operator[](int i) const;
  float* operator[](int i);

  //  Reduced Row Echelon Form using Gaussian - Jordan elimination.
  Matrix24f& rref();

private:
  void swap_rows(float row_a[4], float row_b[4]);
  void multiply_row(float row[4], float value);
  void add_rows(float row_a[4], float row_b[4]);

public:
  //  Print matrix to ostream.
  friend std::ostream& operator<<(std::ostream& s, const Matrix24f& m);
};
