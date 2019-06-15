#include "Matrix44.h"

#include <iostream>
#include <iomanip>
#include <utility>

#include "Matrix33.h"
#include "Matrix48.h"

auto Matrix44f::translation(const Vec3f& t) -> Matrix44f {
  return translation(t.x, t.y, t.z);
}

auto Matrix44f::translation(const float x, const float y, const float z) -> Matrix44f {
  return Matrix44f{
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    x, y, z, 1
  };
}

auto Matrix44f::rotation_x(const float angle) -> Matrix44f {
  return Matrix44f{
    1,  0,               0,               0,
    0,  std::cos(angle), std::sin(angle), 0,
    0, -std::sin(angle), std::cos(angle), 0,
    0,  0,               0,               1
  };
}

auto Matrix44f::rotation_y(const float angle) -> Matrix44f {
  return Matrix44f{
    std::cos(angle), 0, -std::sin(angle), 0,
    0,               1,  0,               0,
    std::sin(angle), 0,  std::cos(angle), 0,
    0,               0,  0,               1
  };
}

auto Matrix44f::rotation_z(const float angle) -> Matrix44f {
  return Matrix44f{
     std::cos(angle), std::sin(angle), 0, 0,
    -std::sin(angle), std::cos(angle), 0, 0,
     0,               0,               1, 0,
     0,               0,               0, 1
  };
}

auto Matrix44f::rotation(const Vec3f& r) -> Matrix44f {
  return rotation(r.x, r.y, r.z);
}

auto Matrix44f::rotation(const float x, const float y, const float z) -> Matrix44f {
  return Matrix44f{}.rotate(x, y, z);
}

auto Matrix44f::scalar(const float s) -> Matrix44f {
  return Matrix44f{
    s, 0, 0, 0,
    0, s, 0, 0,
    0, 0, s, 0,
    0, 0, 0, 1
  };
}

auto Matrix44f::scalar(const Vec3f& s) -> Matrix44f {
  return scalar(s.x, s.y, s.z);
}

auto Matrix44f::scalar(const float x, const float y, const float z) -> Matrix44f {
  return Matrix44f{
    x, 0, 0, 0,
    0, y, 0, 0,
    0, 0, z, 0,
    0, 0, 0, 1
  };
}

Matrix44f::Matrix44f(const bool is_unit_matrix) {
  if (!is_unit_matrix) {
    m[0][0] = 0.0f;
    m[1][1] = 0.0f;
    m[2][2] = 0.0f;
    m[3][3] = 0.0f;
  }
}

Matrix44f::Matrix44f(const float m00, const float m01, const float m02, const float m03,
                     const float m10, const float m11, const float m12, const float m13,
                     const float m20, const float m21, const float m22, const float m23,
                     const float m30, const float m31, const float m32, const float m33) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;

  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

auto Matrix44f::operator[](int i) const -> const Row& {
  return m[i];
}

auto Matrix44f::operator[](int i) -> Row& {
  return m[i];
}

auto Matrix44f::det() const -> float {
  auto m11 = Matrix33f{ m[1][1], m[1][2], m[1][3],
                        m[2][1], m[2][2], m[2][3],
                        m[3][1], m[3][2], m[3][3] };
  auto m12 = Matrix33f{ m[1][0], m[1][2], m[1][3],
                        m[2][0], m[2][2], m[2][3],
                        m[3][0], m[3][2], m[3][3] };
  auto m13 = Matrix33f{ m[1][0], m[1][1], m[1][3],
                        m[2][0], m[2][1], m[2][3],
                        m[3][0], m[3][1], m[3][3] };
  auto m14 = Matrix33f{ m[1][0], m[1][1], m[1][2],
                        m[2][0], m[2][1], m[2][2],
                        m[3][0], m[3][1], m[3][2] };

  return m[0][0] * m11.det() - m[0][1] * m12.det() + m[0][2] * m13.det() - m[0][3] * m14.det();
}

auto Matrix44f::inverse() const -> Matrix44f {
  // XXX: if det() equals 0.00001f for example then the guard clause fails.
  if (det() == 0.0f) {
    std::cerr << "No inverse exists for this matrix.\n";
    return Matrix44f{};
  }
  // Combine the original matrix with a unit matrix to form a 4x8 total matrix.
  auto total_matrix = Matrix48f{ *this };

  // Find the inverse using Gaussian - Jordan elimination.
  return total_matrix.rref().right();
}

auto Matrix44f::translate(const Vec3f& t) -> Matrix44f& {
  return translate(t.x, t.y, t.z);
}

auto Matrix44f::translate(const float x, const float y, const float z) -> Matrix44f& {
  return *this *= translation(x, y, z);
}

auto Matrix44f::rotate_x(const float angle) -> Matrix44f& {
  return *this *= rotation_x(angle);
}

auto Matrix44f::rotate_y(const float angle) -> Matrix44f& {
  return *this *= rotation_y(angle);
}

auto Matrix44f::rotate_z(const float angle) -> Matrix44f& {
  return *this *= rotation_z(angle);
}

auto Matrix44f::rotate(const Vec3f& r) -> Matrix44f& {
  return rotate(r.x, r.y, r.z);
}

auto Matrix44f::rotate(const float x, const float y, const float z) -> Matrix44f& {
  if (z) rotate_z(z);
  if (x) rotate_x(x);
  if (y) rotate_y(y);
  return *this;
}

auto Matrix44f::scale(const float s) -> Matrix44f& {
  return *this *= scalar(s);
}

auto Matrix44f::scale(const Vec3f& s) -> Matrix44f& {
  return scale(s.x, s.y, s.z);
}

auto Matrix44f::scale(const float x, const float y, const float z) -> Matrix44f& {
  return *this *= scalar(x, y, z);
}

Matrix44f Matrix44f::translation() const {
  auto result = Matrix44f{};
  result[3][0] = m[3][0];
  result[3][1] = m[3][1];
  result[3][2] = m[3][2];
  return result;
}

Matrix44f Matrix44f::rotation_and_scale() const {
  auto result = *this;
  result[0][3] = 0;
  result[1][3] = 0;
  result[2][3] = 0;
  result[3][0] = 0;
  result[3][1] = 0;
  result[3][2] = 0;
  result[3][3] = 1;
  return result;
}

auto Matrix44f::operator*=(const Matrix44f& other) -> Matrix44f& {
  return *this = *this * other;
}

auto operator<<(std::ostream& s, const Matrix44f& m) -> std::ostream& {
  auto old_flags = s.flags();
  auto width = 9;
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

auto operator*(const Matrix44f& lhs, const Matrix44f& rhs) -> Matrix44f {
  auto result = Matrix44f{ false };

  for (auto i = 0; i < 4; i++) {
    for (auto j = 0; j < 4; j++) {
      for (auto k = 0; k < 4; k++) {
        result[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }

  return result;
}