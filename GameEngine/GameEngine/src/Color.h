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

  Color& operator=(const Color255& color);

  // Normalize if any one of the colors are greater than 1.0.
  void constrain();

  Color& operator+=(const Color& other);
  Color& operator*=(const Color& other);
  Color& operator*=(const Vec3f& vector);
  Color& operator*=(const float scalar);
};

Color operator*(Color lhs, const Color& rhs);
Color operator*(Color color, const float scalar);
Color operator*(const float scalar, Color color);

class Color255 {
public:
  unsigned char r, g, b;

public:
  Color255();
  Color255(Color color);
  explicit Color255(unsigned char color);
  Color255(unsigned char red, unsigned char green, unsigned char blue);
};
