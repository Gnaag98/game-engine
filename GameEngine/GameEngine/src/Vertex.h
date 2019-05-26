#pragma once

#include <vector>

#include "Vec2.h"
#include "Color.h"

//  TODO: Make it 3D and use it to connect attributes with positions.
class Vertex {
public:
  Vec3f position;
  Vec3f position_projected;
  Color color;

public:
  Vertex();
  explicit Vertex(const Vec3f& position);
  Vertex(const Vec3f& position, const Color& color);
};
