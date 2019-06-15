#pragma once

#include <vector>

#include "Keyframe.h"

class Animation {
public:
  std::vector<Keyframe> keyframes;
  unsigned int current_keyframe = 0u;
  unsigned int current_frame = 0u;
  bool is_animating = true;
  bool is_looping = true;

public:
  // Not [[nodiscard]] to be able to step every frame but only render, for example, every fourth step.
  auto step() -> Transform;
};