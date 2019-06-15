#pragma once

#include <array>
#include <ostream>

class Matrix44f;

// Used when finding the inverse of a 4x4 matrix.
class Matrix48f {
private:
  using Row = std::array<float, 8>;
private:
  std::array<Row, 4> m = {
    Row{1, 0, 0, 0, 1, 0, 0, 0},
    Row{0, 1, 0, 0, 0, 1, 0, 0},
    Row{0, 0, 1, 0, 0, 0, 1, 0},
    Row{0, 0, 0, 1, 0, 0, 0, 1}
  };

public:
  // Inserts a 4x4 matrix into the left half of matrix. 
  Matrix48f(const Matrix44f& other);

  auto operator[](int i) const -> const Row&;
  auto operator[](int i)       ->       Row&;

  // Left half of the total matrix.
  [[nodiscard]]
  auto left() const -> Matrix44f;
  // Right half of the total matrix.
  [[nodiscard]]
  auto right() const -> Matrix44f;

  // Reduced Row Echelon Form using Gaussian - Jordan elimination.
  [[nodiscard]]
  auto rref() -> Matrix48f&;

private:
  void swap_rows(Row& row_a, Row& row_b);
  void multiply_row(Row& row, const float value);
  void add_row(Row& row_a, const Row& row_b);

public:
  friend auto operator<<(std::ostream& ostream, const Matrix48f& matrix) -> std::ostream&;
};