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
  static const float S_DEFAULT_NEAR;
  static const float S_DEFAULT_FAR;
  static const float S_DEFAULT_ASPECT_RATIO;
  static const float S_DEFAULT_FOV;

//public:
//  Matrix44f world_to_camera;
private:
  float m_fov;
  float m_aspect_ratio;
public:
  //  TEMP: near_clipping_plane is used outside the class, therefore public.
  float near_clipping_plane, far_clipping_plane;
private:
  float canvas_top, canvas_right, canvas_bottom, canvas_left;

public:
  Camera();
  Camera(float fov_horizontal, float aspect_ratio,
         float near = S_DEFAULT_NEAR, float far = S_DEFAULT_FAR);

  float fov() const;
  void fov(const float fov_horizontal);
  float aspect_ratio() const;
  void aspect_ratio(float aspect_ratio);

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
