#include "Matrix48.h"

#include <iostream>
#include <iomanip>

#include "Matrix44.h"

Matrix48f::Matrix48f() {}

Matrix48f::Matrix48f(const Matrix44f& other) {
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

const float* Matrix48f::operator[](int i) const {
  return m[i];
}

float* Matrix48f::operator[](int i) {
  return m[i];
}

Matrix48f& Matrix48f::rref() {
  //  Round too small values to 0.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (std::abs(m[i][j]) < 0.00001f) {
        m[i][j] = 0;
      }
    }
  }

  //  Create 1's in the diagonal and 0's underneath.
  for (int i = 0; i < 4; i++) {
    //  Swap rows, if needed, so that there isn't a zero in the diagonal.
    for (int j = i + 1; j < 4; j++) {
      if (m[i][i] != 0.0f) break;
      if (m[j][i] != 0.0f) swap_rows(m[i], m[j]);
    }

    //  Divide row, if needed, so that there is a 1 in the diagonal.
    if (m[i][i] != 1.0f) {
      multiply_row(m[i], 1 / m[i][i]);
    }

    //  Subtract row from the rows below, if needed, so that the column under
    //  m[i][i] is 0.
    for (int j = i + 1; j < 4; j++) {
      if (m[j][i] != 0.0f) {
        float row_i[8] = {m[i][0], m[i][1], m[i][2], m[i][3], m[i][4], m[i][5],
          m[i][6], m[i][7]};
        multiply_row(row_i, -m[j][i]);
        add_rows(row_i, m[j]);
      }
    }
  }

  //  Subtract row from the rows above, if needed, so that the column above
  //  m[i][i] is 0.
  for (int j = 3; j >= 0; j--) {
    for (int i = 0; i < j; i++) {
      if (m[i][j] != 0.0f) {
        float row_j[8] = {m[j][0], m[j][1], m[j][2], m[j][3], m[j][4], m[j][5],
          m[j][6], m[j][7]};
        multiply_row(row_j, -m[i][j]);
        add_rows(row_j, m[i]);
      }
    }
  }

  return *this;
}

void Matrix48f::swap_rows(float row_a[8], float row_b[8]) {
  float temp_row[8];
  //  Copy row A into temp.
  temp_row[0] = row_a[0];
  temp_row[1] = row_a[1];
  temp_row[2] = row_a[2];
  temp_row[3] = row_a[3];
  temp_row[4] = row_a[4];
  temp_row[5] = row_a[5];
  temp_row[6] = row_a[6];
  temp_row[7] = row_a[7];
  //  Copy row B into row A.
  row_a[0] = row_b[0];
  row_a[1] = row_b[1];
  row_a[2] = row_b[2];
  row_a[3] = row_b[3];
  row_a[4] = row_b[4];
  row_a[5] = row_b[5];
  row_a[6] = row_b[6];
  row_a[7] = row_b[7];
  //  Copy temp into row B.
  row_b[0] = temp_row[0];
  row_b[1] = temp_row[1];
  row_b[2] = temp_row[2];
  row_b[3] = temp_row[3];
  row_b[4] = temp_row[4];
  row_b[5] = temp_row[5];
  row_b[6] = temp_row[6];
  row_b[7] = temp_row[7];
}

void Matrix48f::multiply_row(float row[8], float value) {
  row[0] *= value;
  row[1] *= value;
  row[2] *= value;
  row[3] *= value;
  row[4] *= value;
  row[5] *= value;
  row[6] *= value;
  row[7] *= value;
}

void Matrix48f::add_rows(float row_a[8], float row_b[8]) {
  row_b[0] += row_a[0];
  row_b[1] += row_a[1];
  row_b[2] += row_a[2];
  row_b[3] += row_a[3];
  row_b[4] += row_a[4];
  row_b[5] += row_a[5];
  row_b[6] += row_a[6];
  row_b[7] += row_a[7];
}

std::ostream & operator<<(std::ostream & s, const Matrix48f & m) {
  std::ios_base::fmtflags old_flags = s.flags();
  int width = 9;
  s.precision(5);
  s.setf(std::ios_base::fixed);

  s << "|" << std::setw(width) << m[0][0] <<
    " " << std::setw(width) << m[0][1] <<
    " " << std::setw(width) << m[0][2] <<
    " " << std::setw(width) << m[0][3] <<
    " " << std::setw(width) << m[0][4] <<
    " " << std::setw(width) << m[0][5] <<
    " " << std::setw(width) << m[0][6] <<
    " " << std::setw(width) << m[0][7] << " |\n" <<

    "|" << std::setw(width) << m[1][0] <<
    " " << std::setw(width) << m[1][1] <<
    " " << std::setw(width) << m[1][2] <<
    " " << std::setw(width) << m[1][3] <<
    " " << std::setw(width) << m[1][4] <<
    " " << std::setw(width) << m[1][5] <<
    " " << std::setw(width) << m[1][6] <<
    " " << std::setw(width) << m[1][7] << " |\n" <<

    "|" << std::setw(width) << m[2][0] <<
    " " << std::setw(width) << m[2][1] <<
    " " << std::setw(width) << m[2][2] <<
    " " << std::setw(width) << m[2][3] <<
    " " << std::setw(width) << m[2][4] <<
    " " << std::setw(width) << m[2][5] <<
    " " << std::setw(width) << m[2][6] <<
    " " << std::setw(width) << m[2][7] << " |\n" <<

    "|" << std::setw(width) << m[3][0] <<
    " " << std::setw(width) << m[3][1] <<
    " " << std::setw(width) << m[3][2] <<
    " " << std::setw(width) << m[3][3] <<
    " " << std::setw(width) << m[3][4] <<
    " " << std::setw(width) << m[3][5] <<
    " " << std::setw(width) << m[3][6] <<
    " " << std::setw(width) << m[3][7] << " |";

  s.flags(old_flags);
  return s;
}
