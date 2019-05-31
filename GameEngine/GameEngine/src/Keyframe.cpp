#include "Keyframe.h"

#include <iostream>

#include "Vec3.h"
#include "Transform.h"

Keyframe::Keyframe()
  : frame(0), transform() {}

Keyframe::Keyframe(const unsigned int f, const Transform& t)
  : frame(f), transform(t) {}

// Move-optimized constructor for rvalues.
Keyframe::Keyframe(const unsigned int f, Transform&& t)
  : frame(f), transform(std::move(t)) {}

Transform Keyframe::lerp(const Keyframe& start, const Keyframe& end,
                         const unsigned int frame) {
  Transform transform;

  if (frame <= start.frame) {
    transform = start.transform;
  } else if (frame < end.frame) {
    float progress = (frame - start.frame) / float(end.frame - start.frame);
    transform.lerp(start.transform, end.transform, progress);
  } else {
    transform = end.transform;
  }

  return transform;
}
