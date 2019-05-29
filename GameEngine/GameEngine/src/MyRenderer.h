#pragma once

#include <vector>
#include <queue>
#include <future>
#include <mutex>

#include "Camera.h"
#include "ThreadPool.h"

class MyRenderer {
protected:
  ThreadPool m_thread_pool;
  std::queue<std::future<void>> futures;
  // IDEA: Change mutex name.
  mutable std::mutex triangle_mutex;

protected:
  explicit MyRenderer(const int thread_count);
public:
  virtual ~MyRenderer() = default;

public:
  virtual void render_object(const Object& object,
                             const Camera& camera,
                             std::vector<float>& depth_buffer,
                             std::vector<Color255>& frame_buffer,
                             std::vector<Color>& subpixel_buffer,
                             const int image_width, const int image_height,
                             const int anti_aliasing) = 0;
};