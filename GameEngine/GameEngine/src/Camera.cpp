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

//  TEMP: define.
//#define IS_CLOCKING

Camera::Camera()
  : m_fov(S_DEFAULT_FOV),
    m_aspect_ratio(S_DEFAULT_ASPECT_RATIO),
    near_clipping_plane(S_DEFAULT_NEAR),
    far_clipping_plane(S_DEFAULT_FAR)
     {
  const float fov_radians = m_fov * (float)M_PI / 180.0f;
  canvas_right = std::tan(fov_radians / 2.0f) * near_clipping_plane;
  canvas_top = canvas_right / m_aspect_ratio;
  canvas_left = -canvas_right;
  canvas_bottom = -canvas_top;
}

Camera::Camera(float fov_horizontal, float aspect_ratio,
               float near, float far)
  : m_fov(fov_horizontal),
    m_aspect_ratio(aspect_ratio),
    near_clipping_plane(near),
    far_clipping_plane(far)
     {
  set_canvas();
}

float Camera::fov() const {
  return m_fov;
}

void Camera::fov(float fov_horizontal) {
  m_fov = fov_horizontal;
  set_canvas();
}

float Camera::aspect_ratio() const {
  return m_aspect_ratio;
}

void Camera::aspect_ratio(float ratio)  {
  m_aspect_ratio = ratio;
  set_canvas();
}

Matrix44f Camera::world_to_camera() const {
  // XXX: Possibly makes an unnecessary copy. Could solve with std::move().
  return transform.matrix().inverse();
}

void Camera::project_object(Object& object,
                            const int image_width,
                            const int image_height) const {
  //std::cout << "    Projecting object...\n";
  //auto timer_start = std::chrono::high_resolution_clock::now();
  if (!object.mesh) return;

  for (Vertex& vertex : object.mesh->verticies) {
    project_vertex(vertex, object.transform, image_width, image_height);
  }

  //auto timer_end = std::chrono::high_resolution_clock::now();
  //std::chrono::duration<double, std::milli> timer_duration = timer_end - timer_start;
  //std::cout << "    Done projecting object. It took " << timer_duration.count() << " ms\n";
}

void Camera::project_vertex(Vertex& vertex,
                            const Transform& transform,
                            const int image_width,
                            const int image_height) const {
  //std::cout << "    Projecting vertex...\n";
  //auto timer_start = std::chrono::high_resolution_clock::now();

  //std::cout << "\n\nvertex->position_world: " << vertex->position_world << "\n";
  //std::cout << "vertex->position: " << vertex.position << "\n";

  //  World Space -> Camera Space.
  Vec3f point_camera = vertex.position * transform.matrix() * world_to_camera();

  //std::cout << "point_camera: " << point_camera << "\n";

  //  Camera Space -> Screen Space (Canvas).
  Vec2f point_screen;
  /*  CHANGED: Now dividing by abs(z) to prevent x and y from switching signs.
   *           If the point is behind the camera then it's z value will be
   *           Negative, however I just care about the absolute distance. */
  //point_screen.x = point_camera.x / -point_camera.z * near_clipping_plane;
  //point_screen.y = point_camera.y / -point_camera.z * near_clipping_plane;
  point_screen.x = point_camera.x / std::abs(point_camera.z) * near_clipping_plane;
  point_screen.y = point_camera.y / std::abs(point_camera.z) * near_clipping_plane;

  //std::cout << "point_screen: " << point_screen << "\n";

  //  Screen Space -> NDC Space (-1, 1).
  Vec2f point_ndc;
  point_ndc.x = 2 * point_screen.x / (canvas_right - canvas_left) -
    (canvas_right + canvas_left) / (canvas_right - canvas_left);
  point_ndc.y = 2 * point_screen.y / (canvas_top - canvas_bottom) -
    (canvas_top + canvas_bottom) / (canvas_top - canvas_bottom);

  //std::cout << "point_ndc: " << point_ndc << "\n";

//  NDC Space -> Raster Space.
  //Vec3f point_raster;
  //point_raster.x = (point_ndc.x + 1.0f) / 2.0f * image_width;
  //point_raster.y = (1.0f - point_ndc.y) / 2.0f * image_height;
  //point_raster.z = -point_camera.z;
  //
  //return point_raster;
  vertex.position_projected.x = (point_ndc.x + 1.0f) / 2.0f * image_width;
  vertex.position_projected.y = (1.0f - point_ndc.y) / 2.0f * image_height;
  vertex.position_projected.z = -point_camera.z;

  //std::cout << "vertex->position_projected: " << vertex.position_projected << "\n\n\n";


  //auto timer_end = std::chrono::high_resolution_clock::now();
  //std::chrono::duration<double, std::milli> timer_duration = timer_end - timer_start;
  //std::cout << "    Done projecting vertex. It took " << timer_duration.count() << " ms\n";
}

void Camera::set_canvas() {
  const float FOV_RADIANS = float(m_fov * M_PI / 180.0);
  canvas_right = std::tan(FOV_RADIANS / 2.0f) * near_clipping_plane;
  canvas_top = canvas_right / m_aspect_ratio;
  canvas_left = -canvas_right;
  canvas_bottom = -canvas_top;
}