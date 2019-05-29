#include "Animation.h"

Transform Animation::next_frame() {
  Transform result;
  if (keyframes.size() > 0) {
    if (current_keyframe == 0) {
      result = keyframes[0].transform;
      if (keyframes.size() > 1) {
        current_keyframe = 1;
      }
      return result;
    } else if (current_keyframe < keyframes.size()) {
      ++current_frame;
      if (current_frame == keyframes.at(current_keyframe).frame) {
        result = keyframes[current_keyframe].transform;
      } else if (current_frame < keyframes.at(current_keyframe).frame) {
        result = Keyframe::lerp(keyframes[current_frame - 1],
                                keyframes[current_frame],
                                current_frame);
      } else {
        if (current_keyframe + 1 < keyframes.size()) {
          ++current_keyframe;
        } else if (is_looping) {
          current_keyframe = 0;
          current_frame = 0;
        } else {
          // Decrement to counteract the increment. Gives the effect of stopping the counter.
          --current_frame;
        }
      }
    } else {
      result = keyframes.back().transform;
    }
  } else {
    // Throw an error somehow so that the callee knows that the returned default Transform is invalid.
  }
  return result;
}
