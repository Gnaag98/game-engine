#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Camera.h"
#include "Renderer.h"
#include "Object.h"
#include "Color.h"

class Scene {
public:
  struct Settings {
    int image_width = 0;
    int image_height = 0;
    Color255 background_color = Color255::BLACK;
    int anti_aliasing = 1;

    int frame_count = 0;
    bool should_write_to_file = false;
    std::string output_folder = "";
  };

public:
  Settings settings;
  std::weak_ptr<Camera> main_camera;
  // XXX: Not sure if they should be unique or shared pointers.
  std::vector<std::shared_ptr<Object>> objects;
private:
  std::shared_ptr<Renderer> m_renderer;

public:
  explicit Scene(std::shared_ptr<Renderer> renderer);
  void render();

private:
  void write_to_file(const int frame,
                     const std::vector<Color255>& frame_buffer) const;
  void reset_image(std::vector<Color255>& frame_buffer,
                   std::vector<Color>& subpixel_buffer,
                   std::vector<float>& depth_buffer);
};
