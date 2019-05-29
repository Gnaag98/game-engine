#pragma once

#include <string>
#include <vector>

#include "Renderer.h"

#include "Color.h"

class Texture {
private:
  unsigned int m_renderer_id = 0;

public:
  explicit Texture(const std::vector<Color255>& frame_buffer, int width, int height);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind() const;

  auto get_width() const->int;
  auto get_height() const->int;
};