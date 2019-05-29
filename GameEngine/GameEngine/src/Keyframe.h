#pragma once

#include "Vec3.h"
#include "Transform.h"

class Keyframe {
public:
  unsigned int frame;
  Transform transform;

public:
  Keyframe();
  Keyframe(const unsigned int frame, const Transform& transform);
  Keyframe(const unsigned int frame, Transform&& transform);

  static Transform lerp(const Keyframe& start, const Keyframe& end, unsigned int frame);
};
