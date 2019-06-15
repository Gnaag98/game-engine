#include "Rasterizer.h"
#include "MyRenderer.h"

#include <array>
#include <vector>
#include <iostream>
#include <chrono>
#include <functional>
#include <future>
#include <mutex>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "Camera.h"
#include "Triangle.h"
#include "Color.h"
#include "Vec3.h"
#include "Vec2.h"

#include "Matrix22.h"

#include "ThreadPool.h"

Rasterizer::Rasterizer(int thread_count) : MyRenderer{ thread_count } {}

void Rasterizer::render_object(const Object& object,
                               const Camera& camera,
                               std::vector<float>& depth_buffer,
                               std::vector<Color255>& frame_buffer,
                               std::vector<Color>& subpixel_buffer,
                               const int image_width,
                               const int image_height,
                               const int anti_aliasing) {
  if (!object.mesh) return;

  for (const auto& triangle : object.mesh->triangles) {
    using namespace std::placeholders;
    futures.emplace(m_thread_pool.add_task(
      std::bind(&Rasterizer::render_triangle, this,
                std::ref(triangle), std::ref(object.transform), std::ref(camera),
                std::ref(depth_buffer), std::ref(frame_buffer), std::ref(subpixel_buffer),
                image_width, image_height, anti_aliasing, _1)
    ));
  }

  while (futures.size() > 0) {
    futures.front().get();
    futures.pop();
  }

  const auto x_span = 128;
  const auto y_span = 128;
  for (auto i = 0; i < image_height; i += y_span) {
    for (auto j = 0; j < image_width; j += x_span) {
      using namespace std::placeholders;
      futures.emplace(m_thread_pool.add_task(
        std::bind(&Rasterizer::batch_merge_pixels, this,
                  i, j, x_span, y_span, image_width, image_height,
                  std::ref(frame_buffer), std::ref(subpixel_buffer),
                  anti_aliasing, _1)
      ));
    }
  }

  while (futures.size() > 0) {
    futures.front().get();
    futures.pop();
  }
}

void Rasterizer::render_triangle(const Triangle& triangle,
                                 const Transform& transform,
                                 const Camera& camera,
                                 std::vector<float>& depth_buffer,
                                 std::vector<Color255>& frame_buffer,
                                 std::vector<Color>& subpixel_buffer,
                                 const int image_width,
                                 const int image_height,
                                 const int anti_aliasing,
                                 const int thread_id) {

  // OPTIMIZE: Change this array and the color array to an array of pointers.
  //           Maybe that'll speed things up.
  const auto positions = std::array<Vec3f, 3>{
      triangle.verticies[0]->position_projected,
      triangle.verticies[1]->position_projected,
      triangle.verticies[2]->position_projected
  };

  const auto normals_world = std::array<Vec3f, 3>{
    (*triangle.normals[0] * transform.local_to_world_matrix()).normalize(),
    (*triangle.normals[1] * transform.local_to_world_matrix()).normalize(),
    (*triangle.normals[2] * transform.local_to_world_matrix()).normalize()
  };

  // Experimental lights.
  Vec3f light_direction(-3.0f, -0.7f, -1.7f);
  light_direction.normalize();

  // Diffuse surface color.
  //float albeto = 0.18f;
  //float light_intensity = 17;
  //float diffusion = albeto / M_PI * light_intensity * std::max(0.0f, normals_world[0].dot(-light_direction));

  // Simplified version (without albeto and intensity).
  float diffusion = std::max(0.0f, normals_world[0].dot(-light_direction));

  //std::cout << "\n  Normal:\t\t" << normals_world[0] << '\n' << "  Light direction:\t" << light_direction << '\n';
  //std::cout << "  Diffusion\t\t: " << diffusion << "\n\n";

  auto colors = std::array<Color, 3>{
    triangle.verticies[0]->color,
    triangle.verticies[1]->color,
    triangle.verticies[2]->color
  };

  // TEMP: temporary texture test (checker board).
  auto st0 = Vec2f{ 1, 0 };
  auto st1 = Vec2f{ 0, 0 };
  auto st2 = Vec2f{ 0, 1 };

  // TEMP: This bool is only while experimenting.
  auto is_correcting_perspective = true;
  if (is_correcting_perspective) {
    /* OPTIMIZE: Precompute 1 / z.
     * Precompute by setting z = 1 / z for each vector and then in
     * calculations, instead multiply by z instead of dividing by z.  */
    colors[0].r /= positions[0].z;
    colors[0].g /= positions[0].z;
    colors[0].b /= positions[0].z;

    colors[1].r /= positions[1].z;
    colors[1].g /= positions[1].z;
    colors[1].b /= positions[1].z;

    colors[2].r /= positions[2].z;
    colors[2].g /= positions[2].z;
    colors[2].b /= positions[2].z;

    // Experimental lights.
    //std::cout << "    r: " << colors[0].r << '\n';
    //std::cout << "    g: " << colors[0].g << '\n';
    //std::cout << "    b: " << colors[0].b << '\n';
    //
    //std::cout << "    r: " << colors[1].r << '\n';
    //std::cout << "    g: " << colors[1].g << '\n';
    //std::cout << "    b: " << colors[1].b << '\n';
    //
    //std::cout << "    r: " << colors[2].r << '\n';
    //std::cout << "    g: " << colors[2].g << '\n';
    //std::cout << "    b: " << colors[2].b << "\n\n";

    colors[0].r *= diffusion;
    colors[0].g *= diffusion;
    colors[0].b *= diffusion;

    colors[1].r *= diffusion;
    colors[1].g *= diffusion;
    colors[1].b *= diffusion;

    colors[2].r *= diffusion;
    colors[2].g *= diffusion;
    colors[2].b *= diffusion;

    // TEMP: temporary texture test (checker board).
    st0[0] /= positions[0].z;
    st0[1] /= positions[0].z;

    st1[0] /= positions[1].z;
    st1[1] /= positions[1].z;

    st2[0] /= positions[2].z;
    st2[1] /= positions[2].z;
  }

  auto area = edge_function(positions[0], positions[1], positions[2]);

  auto bounding_box_min = Vec2i{ image_width - 1, image_height - 1 };
  auto bounding_box_max = Vec2i{ 0, 0 };
  compute_bounding_box(positions, image_width, image_height,
                       bounding_box_min, bounding_box_max);

  for (auto i = bounding_box_min.y; i <= bounding_box_max.y; ++i) {
    for (auto j = bounding_box_min.x; j <= bounding_box_max.x; ++j) {
      color_subpixels(camera,
                      i, j, anti_aliasing, positions, colors, area,
                      is_correcting_perspective, image_width, image_height,
                      depth_buffer, st0, st1, st2, subpixel_buffer, frame_buffer);
    }
  }
}

void Rasterizer::color_subpixels(const Camera& camera,
                                 const int i, const int j, const int anti_aliasing,
                                 const std::array<Vec3f, 3>& vectors,
                                 const std::array<Color, 3>& colors,
                                 float area, bool is_correcting_perspective,
                                 const int image_width, const int image_height,
                                 std::vector<float>& depth_buffer,
                                 const Vec2f& st0, const Vec2f& st1, const Vec2f& st2,
                                 std::vector<Color>& subpixel_buffer,
                                 std::vector<Color255>& frame_buffer) const {
  for (auto i_sub = 0; i_sub < anti_aliasing; ++i_sub) {
    for (auto j_sub = 0; j_sub < anti_aliasing; ++j_sub) {
      auto subpixel = Vec2f{ j + j_sub / float(anti_aliasing) + 1.0f / anti_aliasing / 2.0f,
                             i + i_sub / float(anti_aliasing) + 1.0f / anti_aliasing / 2.0f };

      auto weights = std::array<float, 3>{};
      weights[0] = edge_function(subpixel, vectors[1], vectors[2]);
      weights[1] = edge_function(subpixel, vectors[2], vectors[0]);
      weights[2] = edge_function(subpixel, vectors[0], vectors[1]);

      auto edge_0 = Vec2f{ vectors[2] - vectors[1] };
      auto edge_1 = Vec2f{ vectors[0] - vectors[2] };
      auto edge_2 = Vec2f{ vectors[1] - vectors[0] };
      auto is_overlapping = true;
      is_overlapping &= top_left_rule(weights[0], edge_0);
      is_overlapping &= top_left_rule(weights[1], edge_1);
      is_overlapping &= top_left_rule(weights[2], edge_2);

      if (is_overlapping) {
        // Normalize weights.
        weights[0] /= area;
        weights[1] /= area;
        weights[2] /= area;

        auto depth = compute_depth(vectors, weights);

        const auto subpixel_index = (i * anti_aliasing + i_sub) * image_width * anti_aliasing
                                    + j * anti_aliasing + j_sub;
        
        auto lock = std::lock_guard<std::mutex>{ triangle_mutex };
        if (depth > camera.near_clipping_plane && depth < depth_buffer[subpixel_index]) {
          depth_buffer[subpixel_index] = depth;

          auto r = weights[0] * colors[0].r + weights[1] * colors[1].r + weights[2] * colors[2].r;
          auto g = weights[0] * colors[0].g + weights[1] * colors[1].g + weights[2] * colors[2].g;
          auto b = weights[0] * colors[0].b + weights[1] * colors[1].b + weights[2] * colors[2].b;

          //  TEMP: temporary texture test (checker board).
          auto s = weights[0] * st0[0] + weights[1] * st1[0] + weights[2] * st2[0];
          auto t = weights[0] * st0[1] + weights[1] * st1[1] + weights[2] * st2[1];

          if (is_correcting_perspective) {
            r *= depth;
            g *= depth;
            b *= depth;

            //  TEMP: temporary texture test (checker board).
            s *= depth;
            t *= depth;
          }

          //  TEMP: temporary texture test (checker board).
          const auto M = 5;
          //bool p = (std::fmod(s * M, 1.0f) > 0.5f) ^ (std::fmod(t * M, 1.0f) < 0.5f);
          auto p = true; // Turns off checker pattern.

          //  TEMP: temporary texture test (checker board).
          if (!p) {
            subpixel_buffer[subpixel_index].r = p;
            subpixel_buffer[subpixel_index].g = p;
            subpixel_buffer[subpixel_index].b = p;
          } else {
            subpixel_buffer[subpixel_index].r = r;
            subpixel_buffer[subpixel_index].g = g;
            subpixel_buffer[subpixel_index].b = b;
          }
        }
      }
    }
  }
}

void Rasterizer::batch_merge_pixels(const int i_part, const int j_part,
                                    const int x_span, const int y_span,
                                    const int image_width, const int image_height,
                                    std::vector<Color255>& frame_buffer,
                                    std::vector<Color>& subpixel_buffer,
                                    const int anti_aliasing,
                                    const int thread_id) const {
  for (auto i = i_part; i < i_part + y_span && i < image_height; ++i) {
    for (auto j = j_part; j < j_part + x_span && j < image_width; ++j) {
      merge_subpixels(i, j, image_width, image_height,
                      frame_buffer, subpixel_buffer,
                      anti_aliasing);
    }
  }
}

void Rasterizer::merge_subpixels(const int i, const int j,
                                 const int image_width, const int image_height,
                                 std::vector<Color255>& frame_buffer,
                                 std::vector<Color>& subpixel_buffer,
                                 const int anti_aliasing) const {
  // TEMP: Hardcoded choice to blend the square of the colors for more accurate results.
  const auto is_squaring = true;
  auto r = 0.0f, g = 0.0f, b = 0.0f;
  for (auto i_sub = 0; i_sub < anti_aliasing; ++i_sub) {
    for (auto j_sub = 0; j_sub < anti_aliasing; ++j_sub) {
      const auto subpixel_index = (i * anti_aliasing + i_sub) * image_width * anti_aliasing
                                  + j * anti_aliasing + j_sub;
      if (is_squaring) {
        r += std::pow(subpixel_buffer[subpixel_index].r, 2);
        g += std::pow(subpixel_buffer[subpixel_index].g, 2);
        b += std::pow(subpixel_buffer[subpixel_index].b, 2);
      } else {
        r += subpixel_buffer[subpixel_index].r;
        g += subpixel_buffer[subpixel_index].g;
        b += subpixel_buffer[subpixel_index].b;
      }
    }
  }

  r /= (anti_aliasing * anti_aliasing);
  g /= (anti_aliasing * anti_aliasing);
  b /= (anti_aliasing * anti_aliasing);

  if (is_squaring) {
    r = std::sqrt(r);
    g = std::sqrt(g);
    b = std::sqrt(b);
  }
  //  NOTE: Intentionally not locking the mutex.
  //        I've made sure the threads are not reading/writing on the same
  //        index of the framebuffer.
  //std::lock_guard<std::mutex> lock(triangle_mutex);
  frame_buffer[i * image_width + j].r = static_cast<unsigned char>(r * 255);
  frame_buffer[i * image_width + j].g = static_cast<unsigned char>(g * 255);
  frame_buffer[i * image_width + j].b = static_cast<unsigned char>(b * 255);
}

auto Rasterizer::edge_function(const Vec2f & point,
                                const Vec2f & vertex_a,
                                const Vec2f & vertex_b) const -> float {
  //  OPTIMIZE: Hardcode the determinant calculation instead of creating a matrix.
  auto matrix = Matrix22f{ point.x - vertex_a.x,    point.y - vertex_a.y,
                           vertex_b.x - vertex_a.x, vertex_b.y - vertex_a.y };
  return matrix.det();
}

//  OPTIMIZE: Custom floor and ceil functions.
void Rasterizer::compute_bounding_box(const std::array<Vec3f, 3> vectors,
                                      const int image_width,
                                      const int image_height,
                                      Vec2i& min, Vec2i& max) const {
  for (const auto& vector : vectors) {
    auto& x = vector.x;
    auto& y = vector.y;

    if (x < min.x) min.x = static_cast<int>(std::floor(x));
    if (y < min.y) min.y = static_cast<int>(std::floor(y));
    if (x > max.x) max.x = static_cast<int>(std::ceil(x));
    if (y > max.y) max.y = static_cast<int>(std::ceil(y));

    if (min.x < 0)                min.x = 0;
    if (min.y < 0)                min.y = 0;
    if (max.x > image_width - 1)  max.x = image_width - 1;
    if (max.y > image_height - 1) max.y = image_height - 1;
  }
}

auto Rasterizer::top_left_rule(const float weight, const Vec2f& edge) const -> bool {
  /*  If point is on the edge (weight == 0), check if edge is either horizontal
   *  and pointing to the right (top edge) or generally pointing
   *  upwards (left edge). Otherwise just check if the edge function returned a
   *  positive value (weigth > 0).  */
  return (weight == 0 ? ((edge.y == 0 && edge.x > 0) || edge.y > 0) : (weight > 0));
}

auto Rasterizer::compute_depth(const std::array<Vec3f, 3> vectors,
                               const std::array<float, 3> weights) const -> float {
  if (vectors[0].z == 0 || vectors[1].z == 0 || vectors[2].z == 0)
    throw std::underflow_error("Dividing by zero when computing depth used in rasterization!\n");

  return 1.0f / (weights[0] / vectors[0].z
                 + weights[1] / vectors[1].z
                 + weights[2] / vectors[2].z);
}