#include "Matrix33.h"

#include <iostream>
#include <iomanip>

#include "Matrix22.h"

Matrix33f::Matrix33f(const float m00, const float m01, const float m02,
                     const float m10, const float m11, const float m12,
                     const float m20, const float m21, const float m22) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
}

auto Matrix33f::operator[](int i) const -> const Row& {
  return m[i];
}

auto Matrix33f::operator[](int i) -> Row& {
  return m[i];
}

auto Matrix33f::det() const -> float {
  auto m11 = Matrix22f{ m[1][1], m[1][2],
                        m[2][1], m[2][2] };
  auto m12 = Matrix22f{ m[1][0], m[1][2],
                        m[2][0], m[2][2] };
  auto m13 = Matrix22f{ m[1][0], m[1][1],
                        m[2][0], m[2][1] };

  return m[0][0] * m11.det() - m[0][1] * m12.det() + m[0][2] * m13.det();
}

auto operator<<(std::ostream& s, const Matrix33f& m) -> std::ostream& {
  auto old_flags = s.flags();
  auto width = 9;
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