#pragma once

#include "Light.h"

class PointLight : public Light {
public:
  PointLight();
  explicit PointLight(const Transform& transform);
  PointLight(const Transform& transform, const float intensity);
  PointLight(const float intensity, const Color& color);
  PointLight(const Transform& transform, const float intensity, const Color& color);
  void illuminate(const Object& object) const override;
};