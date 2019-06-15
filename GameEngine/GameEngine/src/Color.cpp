#include "Color.h"

#include <iostream>
#include <cassert>
#include <algorithm>

Color::Color()
  : r{ 0.0f }, g{ 0.0f }, b{ 0.0f } {}

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
      // Enum defined but no case added to switch statement.
      assert(false);
      r = 0, g = 0, b = 0;
      break;
  }
}

Color::Color(const Vec3f& vector)
  : r{ vector.x }, g{ vector.y }, b{ vector.z } {}

Color::Color(const Color255& color)
  : r{ color.r / 255.0f }, g{ color.g / 255.0f }, b{ color.b / 255.0f } {}

Color::Color(const float color)
  : r{ color }, g{ color }, b{ color } {}

Color::Color(const float red, const float green, const float blue)
  : r{ red }, g{ green }, b{ blue } {
}

auto Color::operator=(const Color255& color) -> Color& {
  r = color.r / 255.0f, g = color.g / 255.0f, b = color.b / 255.0f;
  return *this;
}

void Color::constrain() {
  const auto magnitude_squared = r * r + g * g + b * b;

  // The square of a magnitude can't be negative.
  assert(magnitude_squared >= 0);

  if (magnitude_squared > 1) {
    auto inv_magnitude = 1.0f / std::sqrt(magnitude_squared);
    r *= inv_magnitude, g *= inv_magnitude, b *= inv_magnitude;
  }
}

auto Color::operator+=(const Color& other) -> Color& {
  r += other.r, g += other.g, b += other.b;
  return *this;
}

auto Color::operator*=(const Color& other) -> Color& {
  r *= other.r, g *= other.g, b *= other.b;
  return *this;
}

auto Color::operator*=(const float scalar) -> Color& {
  r *= scalar, g *= scalar, b *= scalar;
  return *this;
}

auto operator*(Color lhs, const Color& rhs) -> Color {
  return std::move(lhs *= rhs);
}

auto operator*(Color color, const float scalar) -> Color {
  return std::move(color *= scalar);
}

auto operator*(const float scalar, Color color) -> Color {
  return std::move(color *= scalar);
}

Color255::Color255()
  : r{ 0 }, g{ 0 }, b{ 0 } {}

Color255::Color255(Color color)
  : r{ 0 }, g{ 0 }, b{ 0 } {
  color.constrain();
  assert(r >= 0 && r <= 255);
  assert(g >= 0 && g <= 255);
  assert(b >= 0 && b <= 255);
  r = unsigned char(color.r * 255);
  g = unsigned char(color.g * 255);
  b = unsigned char(color.b * 255);
}

Color255::Color255(const unsigned char color)
  : r{ color }, g{ color }, b{ color } {}

Color255::Color255(const unsigned char red, const unsigned char green, const unsigned char blue)
  : r{ red }, g{ green }, b{ blue } {}
