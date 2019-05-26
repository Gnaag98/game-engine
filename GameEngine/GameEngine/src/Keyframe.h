#pragma once

#include "Vec3.h"
#include "Transform.h"

class Keyframe {
public:
  int frame;
  Transform transform;

public:
  Keyframe();
  Keyframe(const int frame, const Transform& transform);
  Keyframe(const int frame, Transform&& transform);

  static Transform lerp(const Keyframe& start, const Keyframe& end, int frame);
};
