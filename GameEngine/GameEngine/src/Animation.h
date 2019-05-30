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
  Transform next_frame();
};