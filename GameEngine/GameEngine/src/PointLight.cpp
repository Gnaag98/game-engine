#include "PointLight.h"

#include <algorithm>

PointLight::PointLight()
  : Light{} {}

PointLight::PointLight(const Transform& t)
  : Light{ transform } {}

PointLight::PointLight(const Transform& t, const float i)
  : Light{ t, i } {}

PointLight::PointLight(const float i, const Color& c)
  : Light{ i, c } {}

PointLight::PointLight(const Transform& t, const float i, const Color& c)
  : Light{ t, i, c } {}

void PointLight::illuminate(const Object& object) const {
  if (!object.mesh) return;

  auto object_matrix = object.transform.local_to_world_matrix();
  auto object_rotation = object.transform.rotation_matrix();

  for (auto& triangle : object.mesh->triangles) {
    for (auto i = 0u; i < triangle.verticies.size(); ++i) {
      auto vertex_position = triangle.verticies[i]->position * object_matrix;
      auto normal_world = (*triangle.normals[i] * object_rotation);
      auto light_direction_reverse = (transform.position() - vertex_position).normalize();
      auto cos_angle = std::max(0.0f, normal_world.dot(light_direction_reverse));
      triangle.diffusions[i] += intensity * color * triangle.verticies[i]->color * cos_angle;
    }
  }
}
