#include "DirectionalLight.h"

#include <algorithm>

DirectionalLight::DirectionalLight()
  : Light{} {}

DirectionalLight::DirectionalLight(const Transform& t)
  : Light{ transform } {}

DirectionalLight::DirectionalLight(const Transform& t, const float i)
  : Light{ t, i } {}

DirectionalLight::DirectionalLight(const float i, const Color& c)
  : Light{ i, c } {}

DirectionalLight::DirectionalLight(const Transform& t, const float i, const Color& c)
  : Light{ t, i, c } {}

void DirectionalLight::illuminate(const Object& object) const {
  if (!object.mesh) return;

  auto object_rotation = object.transform.rotation_matrix();
  auto light_direction_reverse = -transform.forward();

  for (auto& triangle : object.mesh->triangles) {
    for (auto i = 0u; i < triangle.verticies.size(); ++i) {
      auto normal_world = (*triangle.normals[i] * object_rotation);
      auto cos_angle = std::max(0.0f, normal_world.dot(light_direction_reverse));
      triangle.diffusions[i] += intensity * color * triangle.verticies[i]->color * cos_angle;
    }
  }
}
