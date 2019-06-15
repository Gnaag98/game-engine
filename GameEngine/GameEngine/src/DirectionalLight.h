#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
  DirectionalLight();
  explicit DirectionalLight(const Transform& transform);
  DirectionalLight(const Transform& transform, const float intensity);
  DirectionalLight(const float intensity, const Color& color);
  DirectionalLight(const Transform& transform, const float intensity, const Color& color);
  void illuminate(const Object& object) const override;
};