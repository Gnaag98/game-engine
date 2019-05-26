#include "Matrix33.h"

#include <iostream>
#include <iomanip>

#include "Matrix22.h"
#include "Matrix36.h"

Matrix33f::Matrix33f() {}

Matrix33f::Matrix33f(const Matrix33f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];
  m[0][2] = other[0][2];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];
  m[1][2] = other[1][2];

  m[2][0] = other[2][0];
  m[2][1] = other[2][1];
  m[2][2] = other[2][2];
}

Matrix33f::Matrix33f(float a, float b, float c,
                     float d, float e, float f,
                     float g, float h, float i) {
  m[0][0] = a;
  m[0][1] = b;
  m[0][2] = c;

  m[1][0] = d;
  m[1][1] = e;
  m[1][2] = f;

  m[2][0] = g;
  m[2][1] = h;
  m[2][2] = i;
}

Matrix33f::Matrix33f(const Matrix36f& other) {
  m[0][0] = other[0][3];
  m[0][1] = other[0][4];
  m[0][2] = other[0][5];

  m[1][0] = other[1][3];
  m[1][1] = other[1][4];
  m[1][2] = other[1][5];

  m[2][0] = other[2][3];
  m[2][1] = other[2][4];
  m[2][2] = other[2][5];
}

Matrix33f& Matrix33f::operator=(const Matrix33f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];
  m[0][2] = other[0][2];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];
  m[1][2] = other[1][2];

  m[2][0] = other[2][0];
  m[2][1] = other[2][1];
  m[2][2] = other[2][2];

  return *this;
}

const float* Matrix33f::operator[](int i) const {
  return m[i];
}

float* Matrix33f::operator[](int i) {
  return m[i];
}

float Matrix33f::det() const {
  Matrix22f m11(m[1][1], m[1][2],
                m[2][1], m[2][2]);
  Matrix22f m12(m[1][0], m[1][2],
                m[2][0], m[2][2]);
  Matrix22f m13(m[1][0], m[1][1],
                m[2][0], m[2][1]);

  return m[0][0] * m11.det() - m[0][1] * m12.det() + m[0][2] * m13.det();
}

Matrix33f Matrix33f::inverse() const {
  if (det() == 0.0f) {
    std::cerr << "No inverse exists for this matrix.\n";
    return Matrix33f();
  }
  //  Combine the original matrix with a unit matrix to form a 3x6 matrix.
  Matrix36f total(*this);

  //  Solve the 3x6 using Gaussian - Jordan elimination and return it as a 3x3.
  return Matrix33f(total.rref());
}

std::ostream& operator<<(std::ostream& s, const Matrix33f& m) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 9;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "|" << std::setw(width) << m[0][0] <<
    " " << std::setw(width) << m[0][1] <<
    " " << std::setw(width) << m[0][2] << " |\n" <<

    "|" << std::setw(width) << m[1][0] <<
    " " << std::setw(width) << m[1][1] <<
    " " << std::setw(width) << m[1][2] << " |\n" <<

    "|" << std::setw(width) << m[2][0] <<
    " " << std::setw(width) << m[2][1] <<
    " " << std::setw(width) << m[2][2] << " |";

  s.flags(old_flags);
  return s;
}