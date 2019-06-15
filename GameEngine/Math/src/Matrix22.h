#pragma once

#include <array>
#include <ostream>

class Matrix22f {
private:
  using Row = std::array<float, 2>;

private:
  std::array<Row, 2> m = {
    Row{1, 0},
    Row{0, 1}
  };

public:
  Matrix22f(const float m00, const float m01,
            const float m10, const float m11);

  auto operator[](const int i) const -> const Row&;
  auto operator[](const int i)       ->       Row&;

  // Determinant.
  auto det() const -> float;

public:
  friend auto operator<<(std::ostream& ostream, const Matrix22f& matrix) -> std::ostream&;
};