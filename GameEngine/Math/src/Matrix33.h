#pragma once

#include <array>
#include <ostream>

class Matrix33f {
private:
  using Row = std::array<float, 3>;

private:
  std::array<Row, 3> m {
    Row{1, 0, 0},
    Row{0, 1, 0},
    Row{0, 0, 1}
  };

public:
  Matrix33f(const float m00, const float m01, const float m02,
            const float m10, const float m11, const float m12,
            const float m20, const float m21, const float m22);

  auto operator[](const int i) const -> const Row&;
  auto operator[](const int i)       ->       Row&;

  // Determinant.
  auto det() const -> float;

public:
  friend auto operator<<(std::ostream& ostream, const Matrix33f& matrix) -> std::ostream&;
};