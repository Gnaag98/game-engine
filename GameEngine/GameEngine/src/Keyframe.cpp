#include "Keyframe.h"

#include <iostream>

#include "Vec3.h"
#include "Transform.h"

Keyframe::Keyframe() : frame(0), transform() {
  std::cout << "[Keyframe] Default constructor.\n";
}

Keyframe::Keyframe(const int f, const Transform& t)
  : frame(f), transform(t) {
  std::cout << "[Keyframe] Parameter constructor.\n";
}

// Move-optimized constructor for rvalues.
Keyframe::Keyframe(const int f, Transform&& t)
  : frame(f), transform(std::move(t)) {
  std::cout << "[Keyframe] Parameter constructor (Move optimized).\n";
}

Transform Keyframe::lerp(const Keyframe& start, const Keyframe& end,
                         const int frame) {
  //std::cout << "Lerping keyframe...\n";
  Transform transform;

  //std::cout << "start.transform.matrix:\n" << start.transform.matrix() << "\n";
  //std::cout << "end.transform.matrix:\n" << end.transform.matrix() << "\n";

  if (frame <= start.frame) {
    //std::cout << "current_frame <= start.frame.\n";
    transform = start.transform;
  } else if (frame < end.frame) {
    float progress = (frame - start.frame) / float(end.frame - start.frame);
    transform.lerp(start.transform, end.transform, progress);
  } else {
    //std::cout << "current_frame >= end.frame.\n";
    transform = end.transform;
  }
  //std::cout << "Done lerping keyframe.\n";
  return transform;
}
