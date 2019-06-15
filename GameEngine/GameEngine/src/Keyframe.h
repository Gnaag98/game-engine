#pragma once

#include "Vec3.h"
#include "Transform.h"

class Keyframe {
public:
  static auto lerp(const Keyframe& start, const Keyframe& end,
                        unsigned int frame) -> Transform;

public:
  unsigned int frame;
  Transform transform;

public:
  Keyframe();
  Keyframe(const unsigned int frame, const Transform& transform);
  // Move-optimized constructor for Transform rvalues.
  Keyframe(const unsigned int frame, Transform&& transform);
};
