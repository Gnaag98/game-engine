#include "Matrix22.h"

#include <iostream>
#include <iomanip>

#include "Matrix24.h"

Matrix22f::Matrix22f() {}

Matrix22f::Matrix22f(const Matrix22f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];
}

Matrix22f::Matrix22f(float a, float b,
                     float c, float d) {
  m[0][0] = a;
  m[0][1] = b;
  m[1][0] = c;
  m[1][1] = d;
}

Matrix22f::Matrix22f(const Matrix24f & other) {
  m[0][0] = other[0][2];
  m[0][1] = other[0][3];

  m[1][0] = other[1][2];
  m[1][1] = other[1][3];
}

Matrix22f& Matrix22f::operator=(const Matrix22f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];

  return *this;
}

const float* Matrix22f::operator[](int i) const {
  return m[i];
}

float* Matrix22f::operator[](int i) {
  return m[i];
}

float Matrix22f::det() const {
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

Matrix22f Matrix22f::inverse() const {
  if (det() == 0.0f) {
    std::cerr << "No inverse exists for this matrix.\n";
    return Matrix22f();
  }
  //  Combine the original matrix with a unit matrix to form a 2x4 matrix.
  Matrix24f total(*this);

  //  Solve the 2x4 using Gaussian - Jordan elimination and return it as a 2x2.
  return Matrix22f(total.rref());
}

std::ostream& operator<<(std::ostream& s, const Matrix22f& m) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 9;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "|" << std::setw(width) << m[0][0] <<
    " " << std::setw(width) << m[0][1] << "\n" <<

    "|" << std::setw(width) << m[1][0] <<
    " " << std::setw(width) << m[1][1] << " |";

  s.flags(old_flags);
  return s;
}
