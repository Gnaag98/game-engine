#include "Camera.h"
#include "Object.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>

#include "Vertex.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Matrix44.h"

const float Camera::S_DEFAULT_NEAR = 0.1f;
const float Camera::S_DEFAULT_FAR = INFINITY;
const float Camera::S_DEFAULT_ASPECT_RATIO = 4.0f / 3.0f;
const float Camera::S_DEFAULT_FOV = 70.0f;

Camera::Camera()
  : m_fov{ S_DEFAULT_FOV },
    m_aspect_ratio{ S_DEFAULT_ASPECT_RATIO },
    near_clipping_plane{ S_DEFAULT_NEAR },
    far_clipping_plane{ S_DEFAULT_FAR } {
  set_canvas();
}

Camera::Camera(const float fov_horizontal, const float aspect_ratio,
               const float near, const float far)
  : m_fov{ fov_horizontal },
    m_aspect_ratio{ aspect_ratio },
    near_clipping_plane{ near },
    far_clipping_plane{ far } {
  set_canvas();
}

auto Camera::fov() const -> float {
  return m_fov;
}

auto Camera::fov(const float fov_horizontal) -> Camera& {
  m_fov = fov_horizontal;
  set_canvas();
  return *this;
}

auto Camera::aspect_ratio() const -> float {
  return m_aspect_ratio;
}

auto Camera::aspect_ratio(const float ratio) -> Camera& {
  m_aspect_ratio = ratio;
  set_canvas();
  return *this;
}

void Camera::project_object(Object& object,
                            const int image_width,
                            const int image_height) const {
  if (!object.mesh) return;

  for (Vertex& vertex : object.mesh->verticies) {
    project_vertex(vertex, object.transform, image_width, image_height);
  }
}

void Camera::project_vertex(Vertex& vertex,
                            const Transform& vertex_transform,
                            const int image_width,
                            const int image_height) const {
  // World Space -> Camera Space.
  const auto point_camera = vertex.position
                            * vertex_transform.local_to_world_matrix()
                            * transform.world_to_local_matrix();

  // Camera Space -> Screen Space (Canvas).
  const auto point_screen = [&] {
    auto point_screen = Vec2f{};
    point_screen.x = point_camera.x / std::abs(point_camera.z) * near_clipping_plane;
    point_screen.y = point_camera.y / std::abs(point_camera.z) * near_clipping_plane;
    return point_screen;
  }();

  // Screen Space -> NDC Space (-1, 1).
  const auto point_ndc = [&] {
    auto point_ndc = Vec2f{};
    point_ndc.x = 2 * point_screen.x / (m_canvas.right - m_canvas.left)
                  - (m_canvas.right + m_canvas.left) / (m_canvas.right - m_canvas.left);
    point_ndc.y = 2 * point_screen.y / (m_canvas.top - m_canvas.bottom)
                  - (m_canvas.top + m_canvas.bottom) / (m_canvas.top - m_canvas.bottom);
    return point_ndc;
  }();

  // NDC Space -> Raster Space.
  vertex.position_projected.x = (point_ndc.x + 1.0f) / 2.0f * image_width;
  vertex.position_projected.y = (1.0f - point_ndc.y) / 2.0f * image_height;
  vertex.position_projected.z = -point_camera.z;
}

void Camera::set_canvas() {
  const auto fov_radians = m_fov * float(M_PI / 180.0);
  m_canvas.right = std::tan(fov_radians / 2.0f) * near_clipping_plane;
  m_canvas.top = m_canvas.right / m_aspect_ratio;
  m_canvas.left = -m_canvas.right;
  m_canvas.bottom = -m_canvas.top;
}