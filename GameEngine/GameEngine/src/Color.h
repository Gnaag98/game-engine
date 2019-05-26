#pragma once

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
  Color(float color);
  Color(float red, float green, float blue);
};


class Color255 {
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

  unsigned char r, g, b;

public:
  Color255();
  Color255(Palette palette);
  Color255(unsigned char color);
  Color255(unsigned char red, unsigned char green, unsigned char blue);
};
