#define _USE_MATH_DEFINES

#include "Scene.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cassert>

#include "Light.h"

Scene::Scene(std::shared_ptr<MyRenderer> renderer)
  : m_renderer{ std::move(renderer) } {
  // Make sure that a valid renderer was added.
  assert(m_renderer);
}

void Scene::render() {
  // Unnecessary as I assert in the constructor, but better safe than sorry.
  if (!m_renderer) {
    std::cerr << "No renderer specified. Can't render scene as a result.\n";
    return;
  }

  auto camera = main_camera.lock();
  if (!camera) {
    std::cerr << "No camera specified. Can't render scene as a result.\n";
    return;
  }

  // Buffers.
  std::vector<Color255> frame_buffer(settings.image_width * settings.image_height);
  std::vector<Color> subpixel_buffer(frame_buffer.size() * settings.anti_aliasing * settings.anti_aliasing);
  std::vector<float> depth_buffer(subpixel_buffer.size());
  std::vector<Vertex*> vertex_buffer;
  std::vector<Triangle*> triangle_buffer;

  int vertex_count = 0;
  int triangle_count = 0;
  for (const auto& object : objects) {
    if (object->mesh) {
      vertex_count += object->mesh->verticies.size();
      vertex_count += object->mesh->triangles.size();
    }
  }
  vertex_buffer.reserve(vertex_count);
  triangle_buffer.reserve(triangle_count);

  for (const auto& object : objects) {
    if (!object->mesh) continue;
    for (Vertex& vertex : object->mesh->verticies) {
      vertex_buffer.emplace_back(&vertex);
    }
    for (Triangle& triangle : object->mesh->triangles) {
      triangle_buffer.emplace_back(&triangle);
    }
  }

  unsigned int next_keyframe = 0;

  double frame_duration_total = 0;
  auto render_start = std::chrono::high_resolution_clock::now();
  for (int frame = 0; frame < settings.frame_count; ++frame) {
    std::cout << "Generating frame " << frame << "...\n";
    auto frame_start = std::chrono::high_resolution_clock::now();

    reset_image(frame_buffer, subpixel_buffer, depth_buffer);

    //if (keyframes.size() > 0) {
    //  if (frame == 0) {
    //    camera.world_to_camera = keyframes[next_keyframe].transform.matrix().inverse();
    //    ++next_keyframe;
    //  } else if (keyframes.size() > next_keyframe) {
    //    camera.world_to_camera = Keyframe::lerp(keyframes[next_keyframe - 1],
    //                                            keyframes[next_keyframe],
    //                                            frame).matrix().inverse();
    //
    //    if (frame == keyframes[next_keyframe].frame - 1) {
    //      ++next_keyframe;
    //    }
    //  }
    //}

    for (auto& object : objects) {
      if (!object->mesh) continue;
      // TEMP: Rotation.
      object->transform.rotate({ 0, M_PI * 2.0 / 60.0, 0 });

      camera->project_object(*object, settings.image_width, settings.image_height);
      m_renderer->render_object(*object, *camera,
                                depth_buffer, frame_buffer, subpixel_buffer,
                                settings.image_width, settings.image_height,
                                settings.anti_aliasing);
    }

    //  Write each frame into a separate file.
    if (settings.should_write_to_file)
      write_to_file(frame, frame_buffer);

    auto frame_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> frame_duration = frame_end - frame_start;
    frame_duration_total += frame_duration.count();

    std::cout << "Frame " << frame << " generated in " << frame_duration.count() << " ms.\n\n";
  }

  auto render_end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> render_duration = render_end - render_start;
  double frame_duration_average = frame_duration_total / settings.frame_count;

  std::cout << settings.frame_count << " frames generated in " << render_duration.count() << " s.\n";
  std::cout << "Average render time per frame: " << frame_duration_average << " ms.\n\n";
}

void Scene::write_to_file(const int frame,
                          const std::vector<Color255>& frame_buffer) const {
  std::ofstream ofs_ppm(std::string("./out/") + settings.output_folder +
                        "/frame_" + std::to_string(frame) + ".ppm",
                        std::ios::binary);

  ofs_ppm << "P6\n";
  ofs_ppm << settings.image_width << " " << settings.image_height << "\n";
  ofs_ppm << "255 ";

  const auto buffer_start = reinterpret_cast<const char*>(&frame_buffer[0]);
  const auto buffer_size = frame_buffer.size() * sizeof(Color255);
  ofs_ppm.write(buffer_start, buffer_size);

  ofs_ppm.close();
}

void Scene::reset_image(std::vector<Color255>& frame_buffer,
                        std::vector<Color>& subpixel_buffer,
                        std::vector<float>& depth_buffer) {
  //  Fill with background color and set depth_buffer to infinity.
  std::fill(frame_buffer.begin(), frame_buffer.end(), settings.background_color);
  //  XXX: Hardcoded value for background.
  std::fill(subpixel_buffer.begin(), subpixel_buffer.end(), 51.0f / 255.0f);
  std::fill(depth_buffer.begin(), depth_buffer.end(), INFINITY);
}
