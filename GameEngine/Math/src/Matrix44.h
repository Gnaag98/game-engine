#pragma once

#include <array>
#include <ostream>

#include "Matrix48.h"
#include "Vec3.h"

class Matrix44f {
private:
  using Row = std::array<float, 4>;

public:
  [[nodiscard]]
  static auto translation(const Vec3f& translation) -> Matrix44f;
  [[nodiscard]]
  static auto translation(const float x, const float y, const float z) -> Matrix44f;

  [[nodiscard]]
  static auto rotation_x(const float angle) -> Matrix44f;
  [[nodiscard]]
  static auto rotation_y(const float angle) -> Matrix44f;
  [[nodiscard]]
  static auto rotation_z(const float angle) -> Matrix44f;
  [[nodiscard]]
  static auto rotation(const Vec3f& rotation) -> Matrix44f;
  [[nodiscard]]
  static auto rotation(const float x, const float y, const float z) -> Matrix44f;

  [[nodiscard]]
  static auto scalar(const float scalar) -> Matrix44f;
  [[nodiscard]]
  static auto scalar(const Vec3f& scalar) -> Matrix44f;
  [[nodiscard]]
  static auto scalar(float x, const float y, const float z) -> Matrix44f;

private:
  std::array<Row, 4> m = {
    Row{1, 0, 0, 0},
    Row{0, 1, 0, 0},
    Row{0, 0, 1, 0},
    Row{0, 0, 0, 1}
  };

public:
  explicit Matrix44f(const bool is_unit_matrix = true);
  Matrix44f(const float m00, const float m01, const float m02, const float m03,
            const float m10, const float m11, const float m12, const float m13,
            const float m20, const float m21, const float m22, const float m23,
            const float m30, const float m31, const float m32, const float m33);

  auto operator[](int i) const -> const Row&;
  auto operator[](int i)       ->       Row&;

  // Determinant.
  [[nodiscard]]
  auto det() const -> float;
  [[nodiscard]]
  auto inverse() const -> Matrix44f;

  auto translate(const Vec3f& translation) -> Matrix44f&;
  auto translate(const float x, const float y, const float z) -> Matrix44f&;
  
  auto rotate_x(const float angle) -> Matrix44f&;
  auto rotate_y(const float angle) -> Matrix44f&;
  auto rotate_z(const float angle) -> Matrix44f&;
  auto rotate(const Vec3f& rotation) -> Matrix44f&;
  auto rotate(const float x, const float y, const float z) -> Matrix44f&;
  
  auto scale(const float scalar) -> Matrix44f&;
  auto scale(const Vec3f& scalar) -> Matrix44f&;
  auto scale(const float x, const float y, const float z) -> Matrix44f&;

  [[nodiscard]]
  auto translation() const -> Matrix44f;
  [[nodiscard]]
  auto rotation_and_scale() const -> Matrix44f;

  auto operator*=(const Matrix44f& other) -> Matrix44f&;
public:
  friend auto operator<<(std::ostream& ostream, const Matrix44f& matrix) -> std::ostream&;
};

[[nodiscard]]
auto operator*(const Matrix44f& lhs, const Matrix44f& rhs) -> Matrix44f;