#include "Matrix44.h"

#include <iostream>
#include <iomanip>
#include <utility>

#include "Matrix33.h"
#include "Matrix48.h"

Matrix44f::Matrix44f(bool is_unit_matrix) {
  if (is_unit_matrix == false) {
    m[0][0] = 0.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = 0.0f;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 0.0f;
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 0.0f;
  }
}

Matrix44f::Matrix44f(const Matrix44f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];
  m[0][2] = other[0][2];
  m[0][3] = other[0][3];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];
  m[1][2] = other[1][2];
  m[1][3] = other[1][3];

  m[2][0] = other[2][0];
  m[2][1] = other[2][1];
  m[2][2] = other[2][2];
  m[2][3] = other[2][3];

  m[3][0] = other[3][0];
  m[3][1] = other[3][1];
  m[3][2] = other[3][2];
  m[3][3] = other[3][3];
}

Matrix44f::Matrix44f(float a, float b, float c, float d,
                     float e, float f, float g, float h,
                     float i, float j, float k, float l,
                     float n, float o, float p, float q) {
  m[0][0] = a;
  m[0][1] = b;
  m[0][2] = c;
  m[0][3] = d;

  m[1][0] = e;
  m[1][1] = f;
  m[1][2] = g;
  m[1][3] = h;

  m[2][0] = i;
  m[2][1] = j;
  m[2][2] = k;
  m[2][3] = l;

  m[3][0] = n;
  m[3][1] = o;
  m[3][2] = p;
  m[3][3] = q;
}

Matrix44f::Matrix44f(const Matrix48f& other) {
  m[0][0] = other[0][4];
  m[0][1] = other[0][5];
  m[0][2] = other[0][6];
  m[0][3] = other[0][7];

  m[1][0] = other[1][4];
  m[1][1] = other[1][5];
  m[1][2] = other[1][6];
  m[1][3] = other[1][7];

  m[2][0] = other[2][4];
  m[2][1] = other[2][5];
  m[2][2] = other[2][6];
  m[2][3] = other[2][7];

  m[3][0] = other[3][4];
  m[3][1] = other[3][5];
  m[3][2] = other[3][6];
  m[3][3] = other[3][7];
}

Matrix44f& Matrix44f::operator=(const Matrix44f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];
  m[0][2] = other[0][2];
  m[0][3] = other[0][3];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];
  m[1][2] = other[1][2];
  m[1][3] = other[1][3];

  m[2][0] = other[2][0];
  m[2][1] = other[2][1];
  m[2][2] = other[2][2];
  m[2][3] = other[2][3];

  m[3][0] = other[3][0];
  m[3][1] = other[3][1];
  m[3][2] = other[3][2];
  m[3][3] = other[3][3];

  return *this;
}

const float* Matrix44f::operator[](int i) const {
  return m[i];
}

float* Matrix44f::operator[](int i) {
  return m[i];
}

float Matrix44f::det() const {
  Matrix33f m11(m[1][1], m[1][2], m[1][3],
                m[2][1], m[2][2], m[2][3],
                m[3][1], m[3][2], m[3][3]);
  Matrix33f m12(m[1][0], m[1][2], m[1][3],
                m[2][0], m[2][2], m[2][3],
                m[3][0], m[3][2], m[3][3]);
  Matrix33f m13(m[1][0], m[1][1], m[1][3],
                m[2][0], m[2][1], m[2][3],
                m[3][0], m[3][1], m[3][3]);
  Matrix33f m14(m[1][0], m[1][1], m[1][2],
                m[2][0], m[2][1], m[2][2],
                m[3][0], m[3][1], m[3][2]);

  return m[0][0] * m11.det() - m[0][1] * m12.det() + m[0][2] * m13.det() -
    m[0][3] * m14.det();
}

Matrix44f Matrix44f::inverse() const {
  if (det() == 0.0f) {
    std::cerr << "No inverse exists for this matrix.\n";
    return Matrix44f();
  }
  //  Combine the original matrix with a unit matrix to form a 4x8 matrix.
  Matrix48f total(*this);

  //  Solve the 4x8 using Gaussian - Jordan elimination and return it as a 4x4.
  return Matrix44f(total.rref());
}

Matrix44f Matrix44f::operator*(const Matrix44f& other) const {
  Matrix44f result(false);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += m[i][k] * other[k][j];
      }
    }
  }

  return result;
}

Matrix44f& Matrix44f::operator*=(const Matrix44f& other) {
  return *this = *this * other;
}

Matrix44f Matrix44f::translation(const Vec3f& t) {
  return std::move(translation(t.x, t.y, t.z));
}

Matrix44f Matrix44f::translation(float x, float y, float z) {
  return Matrix44f(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    x, y, z, 1
  );
}

Matrix44f& Matrix44f::translate(const Vec3f& t) {
  return translate(t.x, t.y, t.z);
}

Matrix44f& Matrix44f::translate(float x, float y, float z) {
  return *this *= translation(x, y, z);
}

Matrix44f Matrix44f::translation() const {
  auto result = Matrix44f{};
  result[3][0] = m[3][0];
  result[3][1] = m[3][1];
  result[3][2] = m[3][2];
  return result;
}

Matrix44f& Matrix44f::rotate_x(float angle) {
  return *this *= rotation_x(angle);
}

Matrix44f& Matrix44f::rotate_y(float angle) {
  return *this *= rotation_y(angle);
}

Matrix44f& Matrix44f::rotate_z(float angle) {
  return *this *= rotation_z(angle);
}

Matrix44f& Matrix44f::rotate(const Vec3f& r) {
  return rotate(r.x, r.y, r.z);
}

Matrix44f& Matrix44f::rotate(float x, float y, float z) {
  if (z) rotate_z(z);
  if (x) rotate_x(x);
  if (y) rotate_y(y);
  return *this;
}

Matrix44f Matrix44f::rotation_x(float angle) {
  return Matrix44f(
    1, 0, 0, 0,
    0, std::cos(angle), std::sin(angle), 0,
    0, -std::sin(angle), std::cos(angle), 0,
    0, 0, 0, 1
  );
}

Matrix44f Matrix44f::rotation_y(float angle) {
  return Matrix44f(
    std::cos(angle), 0, -std::sin(angle), 0,
    0, 1, 0, 0,
    std::sin(angle), 0, std::cos(angle), 0,
    0, 0, 0, 1
  );
}

Matrix44f Matrix44f::rotation_z(float angle) {
  return Matrix44f(
    std::cos(angle), std::sin(angle), 0, 0,
    -std::sin(angle), std::cos(angle), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );
}

Matrix44f Matrix44f::rotation(const Vec3f& r) {
  return std::move(rotation(r.x, r.y, r.z));
}

Matrix44f Matrix44f::rotation(float x, float y, float z) {
  return std::move(Matrix44f{}.rotate(x, y, z));
}

Matrix44f Matrix44f::scalar(float s) {
  return Matrix44f(
    s, 0, 0, 0,
    0, s, 0, 0,
    0, 0, s, 0,
    0, 0, 0, 1
  );
}

Matrix44f Matrix44f::scalar(const Vec3f& s) {
  return std::move(scalar(s.x, s.y, s.z));
}

Matrix44f Matrix44f::scalar(float x, float y, float z) {
  return Matrix44f(
    x, 0, 0, 0,
    0, y, 0, 0,
    0, 0, z, 0,
    0, 0, 0, 1
  );
}

Matrix44f& Matrix44f::scale(float s) {
  return *this *= scalar(s);
}

Matrix44f& Matrix44f::scale(const Vec3f& s) {
  return scale(s.x, s.y, s.z);
}

Matrix44f& Matrix44f::scale(float x, float y, float z) {
  return *this *= scalar(x, y, z);
}

Matrix44f Matrix44f::rotation_and_scale() const {
  auto result = *this;
  result[0][3] = 0;
  result[1][3] = 0;
  result[2][3] = 0;
  result[3][3] = 1;
  result[3][0] = 0;
  result[3][1] = 0;
  result[3][2] = 0;
  return result;
}

std::ostream& operator<<(std::ostream& s, const Matrix44f& m) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 9;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "|" << std::setw(width) << m[0][0] <<
    " " << std::setw(width) << m[0][1] <<
    " " << std::setw(width) << m[0][2] <<
    " " << std::setw(width) << m[0][3] << " |\n" <<

    "|" << std::setw(width) << m[1][0] <<
    " " << std::setw(width) << m[1][1] <<
    " " << std::setw(width) << m[1][2] <<
    " " << std::setw(width) << m[1][3] << " |\n" <<

    "|" << std::setw(width) << m[2][0] <<
    " " << std::setw(width) << m[2][1] <<
    " " << std::setw(width) << m[2][2] <<
    " " << std::setw(width) << m[2][3] << " |\n" <<

    "|" << std::setw(width) << m[3][0] <<
    " " << std::setw(width) << m[3][1] <<
    " " << std::setw(width) << m[3][2] <<
    " " << std::setw(width) << m[3][3] << " |";

  s.flags(old_flags);
  return s;
}