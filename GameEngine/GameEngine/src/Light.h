#pragma once

#include "Object.h"

#include "Color.h"

class Light : public Object {
protected:
  float intensity = 1;
  Color color = Color::WHITE;

public:
  Light();
  explicit Light(const Transform& transform);
  explicit Light(const float intensity);
  Light(const Transform& transform, const float intensity);
  Light(const float intensity, const Color& color);
  Light(const Transform& transform, const float intensity, const Color& color);
  virtual ~Light() = default;

  virtual void illuminate(const Object& object) const = 0;
};
