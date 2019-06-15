#pragma once

#include "Object.h"

#include <vector>

#include "Vertex.h"
#include "Vec3.h"
#include "Matrix44.h"
#include "Object.h"

// TODO: Inherit from Object.
class Camera : public Object {
private:
  struct Canvas {
    float top, right, bottom, left;
  };

private:
  static const float S_DEFAULT_NEAR;
  static const float S_DEFAULT_FAR;
  static const float S_DEFAULT_ASPECT_RATIO;
  static const float S_DEFAULT_FOV;

private:
  float m_fov;
  float m_aspect_ratio;
public:
  // TEMP: near_clipping_plane is used outside the class, therefore public.
  float near_clipping_plane, far_clipping_plane;
private:
  Canvas m_canvas;

public:
  Camera();
  Camera(const float fov_horizontal, const float aspect_ratio,
         const float near_clipping_plane = S_DEFAULT_NEAR,
         const float far_clipping_plane = S_DEFAULT_FAR);

  [[nodiscard]]
  auto fov() const -> float;
  auto fov(const float fov_horizontal) -> Camera&;
  [[nodiscard]]
  auto aspect_ratio() const -> float;
  auto aspect_ratio(const float aspect_ratio) -> Camera&;

  void project_object(Object& object,
                      const int image_width,
                      const int image_height) const;

  void project_vertex(Vertex& vertex,
                      const Transform& vertex_transform,
                      const int image_width,
                      const int image_height) const;
private:
  void set_canvas();
};
