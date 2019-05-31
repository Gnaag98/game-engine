#include "Animation.h"

#include <stdexcept>

Transform Animation::step() {
  auto result = Transform{};
  if (!keyframes.empty()) {
    if (current_keyframe == 0) {
      result = keyframes[0].transform;
      if (keyframes.size() > 1) {
        current_keyframe = 1;
      }
      return result;
    } else if (current_keyframe < keyframes.size()) {
      ++current_frame;
      if (current_frame < keyframes.at(current_keyframe).frame) {
        result = Keyframe::lerp(keyframes[current_keyframe - 1],
                                keyframes[current_keyframe],
                                current_frame);
      } else {
        if (current_keyframe + 1 < keyframes.size()) {
          ++current_keyframe;
          result = Keyframe::lerp(keyframes[current_keyframe - 1],
                                  keyframes[current_keyframe],
                                  current_frame);
        } else if (is_looping) {
          current_keyframe = 0;
          current_frame = 0;
          result = keyframes.front().transform;
        } else {
          // Decrement to counteract the increment. Gives the effect of stopping the counter.
          --current_frame;
          result = keyframes.back().transform;
        }
      }
    } else {
      throw std::out_of_range("Trying to access keyframe out of range.");
    }
  } else {
    throw std::runtime_error("Trying to animate without any keyframes.");
  }
  return result;
}
