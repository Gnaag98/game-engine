#pragma once

#include "Light.h"

class AmbientLight : public Light {
public:
  AmbientLight();
  explicit AmbientLight(const float intensity);
  AmbientLight(const float intensity, const Color& color);
  void illuminate(const Object& object) const override;
};