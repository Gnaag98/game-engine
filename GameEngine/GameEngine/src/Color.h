#pragma once

#include "Vec3.h"

class Color255;

class Color {
public:
  enum Palette {
    RED = 0,
    GREEN,
    BLUE,
    CYAN,
    MAGENTA,
    YELLOW,
    BLACK,
    WHITE
  };

  float r, g, b;

public:
  Color();
  Color(Palette palette);
  Color(const Vec3f& vector);
  explicit Color(const Color255& color);
  explicit Color(float color);
  Color(float red, float green, float blue);

  auto operator=(const Color255& color) -> Color&;

  // Normalize if any one of the colors are greater than 1.0.
  void constrain();

  auto operator+=(const Color& other) -> Color&;
  auto operator*=(const Color& other) -> Color&;
  auto operator*=(const float scalar) -> Color&;
};

[[nodiscard]]
auto operator*(Color lhs, const Color& rhs) -> Color;
[[nodiscard]]
auto operator*(Color color, const float scalar) -> Color;
[[nodiscard]]
auto operator*(const float scalar, Color color) -> Color;

class Color255 {
public:
  unsigned char r, g, b;

public:
  Color255();
  Color255(Color color);
  explicit Color255(unsigned char color);
  Color255(unsigned char red, unsigned char green, unsigned char blue);
};
