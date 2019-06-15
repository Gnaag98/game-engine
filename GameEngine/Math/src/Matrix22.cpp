#include "Matrix22.h"

#include <iostream>
#include <iomanip>

Matrix22f::Matrix22f(const float m00, const float m01,
                     const float m10, const float m11) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[1][0] = m10;
  m[1][1] = m11;
}

auto Matrix22f::operator[](const int i) const -> const Row& {
  return m[i];
}

auto Matrix22f::operator[](const int i) -> Row& {
  return m[i];
}

auto Matrix22f::det() const -> float {
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

std::ostream& operator<<(std::ostream& s, const Matrix22f& m) {
  auto old_flags = s.flags();
  auto width = 9;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "|" << std::setw(width) << m[0][0] <<
       " " << std::setw(width) << m[0][1] << "\n" <<
       
       "|" << std::setw(width) << m[1][0] <<
       " " << std::setw(width) << m[1][1] << " |";

  s.flags(old_flags);
  return s;
}
