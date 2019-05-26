#include "Matrix24.h"

#include <iostream>
#include <iomanip>

#include "Matrix22.h"

Matrix24f::Matrix24f() {}

Matrix24f::Matrix24f(const Matrix22f& other) {
  m[0][0] = other[0][0];
  m[0][1] = other[0][1];

  m[1][0] = other[1][0];
  m[1][1] = other[1][1];
}

const float* Matrix24f::operator[](int i) const {
  return m[i];
}

float* Matrix24f::operator[](int i) {
  return m[i];
}

Matrix24f& Matrix24f::rref() {
  //  Create 1's in the diagonal and 0's underneath.
  for (int i = 0; i < 2; i++) {
    //  Swap rows, if needed, so that there isn't a zero in the diagonal.
    for (int j = i + 1; j < 2; j++) {
      if (m[i][i] != 0.0f) break;
      if (m[j][i] != 0.0f) swap_rows(m[i], m[j]);
    }

    //  Divide row, if needed, so that there is a 1 in the diagonal.
    if (m[i][i] != 1.0f) {
      multiply_row(m[i], 1 / m[i][i]);
    }

    //  Subtract row from the rows below, if needed, so that the column under
    //  m[i][i] is 0.
    for (int j = i + 1; j < 2; j++) {
      if (m[j][i] != 0.0f) {
        float row_i[4] = {m[i][0], m[i][1], m[i][2], m[i][3]};
        multiply_row(row_i, -m[j][i]);
        add_rows(row_i, m[j]);
      }
    }
  }

  //  Subtract row from the rows above, if needed, so that the column above
  //  m[i][i] is 0.
  for (int j = 1; j >= 0; j--) {
    for (int i = 0; i < j; i++) {
      if (m[i][j] != 0.0f) {
        float row_j[4] = {m[j][0], m[j][1], m[j][2], m[j][3]};
        multiply_row(row_j, -m[i][j]);
        add_rows(row_j, m[i]);
      }
    }
  }

  return *this;
}

void Matrix24f::swap_rows(float row_a[4], float row_b[4]) {
  float temp_row[4];
  //  Copy row A into temp.
  temp_row[0] = row_a[0];
  temp_row[1] = row_a[1];
  temp_row[2] = row_a[2];
  temp_row[3] = row_a[3];
  //  Copy row B into row A.
  row_a[0] = row_b[0];
  row_a[1] = row_b[1];
  row_a[2] = row_b[2];
  row_a[3] = row_b[3];
  //  Copy temp into row B.
  row_b[0] = temp_row[0];
  row_b[1] = temp_row[1];
  row_b[2] = temp_row[2];
  row_b[3] = temp_row[3];
}

void Matrix24f::multiply_row(float row[4], float value) {
  row[0] *= value;
  row[1] *= value;
  row[2] *= value;
  row[3] *= value;
}

void Matrix24f::add_rows(float row_a[4], float row_b[4]) {
  row_b[0] += row_a[0];
  row_b[1] += row_a[1];
  row_b[2] += row_a[2];
  row_b[3] += row_a[3];
}

std::ostream& operator<<(std::ostream& s, const Matrix24f& m) {
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
    " " << std::setw(width) << m[1][3] << " |";

  s.flags(old_flags);
  return s;
}
