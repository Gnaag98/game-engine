#include "Color.h"

#include <iostream>

Color::Color() : r(0.0f), g(0.0f), b(0.0f) {}

Color::Color(Palette palette) {
  switch (palette) {
    case Color::RED:
      r = 1, g = 0, b = 0;
      break;
    case Color::GREEN:
      r = 0, g = 1, b = 0;
      break;
    case Color::BLUE:
      r = 0, g = 0, b = 1;
      break;
    case Color::CYAN:
      r = 0, g = 1, b = 1;
      break;
    case Color::MAGENTA:
      r = 1, g = 0, b = 1;
      break;
    case Color::YELLOW:
      r = 1, g = 1, b = 0;
      break;
    case Color::BLACK:
      r = 0, g = 0, b = 0;
      break;
    case Color::WHITE:
      r = 1, g = 1, b = 1;
      break;
    default:
      std::cerr << "Enum defined but no case added to switch statement.\n";
      r = 0, g = 0, b = 0;
      break;
  }
}

Color::Color(float color) : r(color), g(color), b(color) {}

Color::Color(float red, float green, float blue)
  : r(red), g(green), b(blue) {
}

Color255::Color255() : r(0), g(0), b(0) {}

Color255::Color255(Palette palette) {
  switch (palette) {
    case Color255::RED:
      r = 255, g = 0, b = 0;
      break;
    case Color255::GREEN:
      r = 0, g = 255, b = 0;
      break;
    case Color255::BLUE:
      r = 0, g = 0, b = 255;
      break;
    case Color255::CYAN:
      r = 0, g = 255, b = 255;
      break;
    case Color255::MAGENTA:
      r = 255, g = 0, b = 255;
      break;
    case Color255::YELLOW:
      r = 255, g = 255, b = 0;
      break;
    case Color255::BLACK:
      r = 0, g = 0, b = 0;
      break;
    case Color255::WHITE:
      r = 255, g = 255, b = 255;
      break;
    default:
      std::cerr << "Enum defined but no case added to switch statement.\n";
      r = 0, g = 0, b = 0;
      break;
  }
}

Color255::Color255(unsigned char color) : r(color), g(color), b(color) {}

Color255::Color255(unsigned char red, unsigned char green, unsigned char blue)
  : r(red), g(green), b(blue) {}
