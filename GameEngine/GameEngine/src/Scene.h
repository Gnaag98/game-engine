#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Camera.h"
#include "MyRenderer.h"
#include "Object.h"
#include "Color.h"

class Scene {
public:
  struct Settings {
    int image_width = 0;
    int image_height = 0;
    Color background_color = Color::BLACK;
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
  std::shared_ptr<MyRenderer> m_renderer;

public:
  explicit Scene(std::shared_ptr<MyRenderer> renderer);

  auto render() -> int;

private:
  void update();
  void draw(std::vector<Color255>& frame_buffer,
            std::vector<Color>& subpixel_buffer,
            std::vector<float>& depth_buffer,
            const Camera& camera);
  void write_frame_to_file(const int frame,
                           const std::vector<Color255>& frame_buffer) const;
  void reset_image(std::vector<Color255>& frame_buffer,
                   std::vector<Color>& subpixel_buffer,
                   std::vector<float>& depth_buffer);
};
