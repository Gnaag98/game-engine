#pragma once

#include "MyRenderer.h"

#include <array>
#include <vector>
#include <queue>
#include <future>
#include <mutex>

#include "Camera.h"
#include "Triangle.h"
#include "Color.h"
#include "ThreadPool.h"
#include "Object.h"

class Rasterizer : public MyRenderer {
public:
  Rasterizer(int thread_count);

  void render_object(const Object& object,
                     const Camera& camera,
                     std::vector<float>& depth_buffer,
                     std::vector<Color255>& frame_buffer,
                     std::vector<Color>& subpixel_buffer,
                     const int image_width, const int image_height,
                     const int anti_aliasing) override;
private:
  void render_triangle(const Triangle& triangle,
                       const Transform& transform,
                       const Camera& camera,
                       std::vector<float>& depth_buffer,
                       std::vector<Color255>& frame_buffer,
                       std::vector<Color>& subpixel_buffer,
                       const int image_width, const int image_height,
                       const int anti_aliasing,
                       const int thread_id);
  void color_subpixels(const Camera& camera,
                       const int i, const int j, const int anti_aliasing,
                       const std::array<Vec3f, 3>& vectors,
                       const std::array<Color, 3>& colors,
                       float area, bool is_correcting_perspective,
                       const int image_width, const int image_height,
                       std::vector<float>& depth_buffer,
                       const Vec2f& st0, const Vec2f& st1, const Vec2f& st2,
                       std::vector<Color>& subpixel_buffer,
                       std::vector<Color255>& frame_buffer) const;
  void batch_merge_pixels(const int i_part, const int j_part,
                          const int x_span, const int y_span,
                          const int image_width, const int image_height,
                          std::vector<Color255>& frame_buffer,
                          std::vector<Color>& subpixel_buffer,
                          const int anti_aliasing,
                          const int thread_id) const;
  void merge_subpixels(const int i, const int j,
                       const int image_width, const int image_height,
                       std::vector<Color255>& frame_buffer,
                       std::vector<Color>& subpixel_buffer,
                       const int anti_aliasing) const;
  [[nodiscard]]
  auto edge_function(const Vec2f& point,
                      const Vec2f& vertex_a,
                      const Vec2f& vertex_b) const -> float;
  void compute_bounding_box(const std::array<Vec3f, 3> vectors,
                            const int image_width, const int image_height,
                            Vec2i& min, Vec2i& max) const;
private:
  [[nodiscard]]
  auto top_left_rule(const float weight, const Vec2f& edge) const -> bool;
  [[nodiscard]]
  auto compute_depth(const std::array<Vec3f, 3> vectors,
                     const std::array<float, 3> weights) const -> float;
};
