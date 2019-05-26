#pragma once

#include "Vertex.h"
#include "Vec3.h"
#include "Color.h"

// TODO: Make Light inherit from Object instead of Vertex.
class Light : public Vertex {
public:
  Light();
  explicit Light(const Vec3f& position);
  Light(const Vec3f& position, const Color& color);
  // TODO: Add more constructors.
};