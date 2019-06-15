#include "Keyframe.h"

#include <iostream>

#include "Vec3.h"
#include "Transform.h"

Keyframe::Keyframe()
  : frame{ 0 }, transform{} {}

Keyframe::Keyframe(const unsigned int f, const Transform& t)
  : frame{ f }, transform{ t } {}


Keyframe::Keyframe(const unsigned int f, Transform&& t)
  : frame{ f }, transform{ std::move(t) } {}

Transform Keyframe::lerp(const Keyframe& start, const Keyframe& end,
                         const unsigned int frame) {
  if (frame <= start.frame) {
    return start.transform;
  } else if (frame < end.frame) {
    auto progress = (frame - start.frame) / float(end.frame - start.frame);
    return Transform{}.lerp_locally(start.transform, end.transform, progress);
  } else {
    return end.transform;
  }
}
