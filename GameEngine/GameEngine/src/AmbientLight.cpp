#include "AmbientLight.h"

AmbientLight::AmbientLight()
  : Light{} {}

AmbientLight::AmbientLight(const float i)
  : Light{ i } {}

AmbientLight::AmbientLight(const float i, const Color& c)
  : Light{ i, c } {}

void AmbientLight::illuminate(const Object& object) const {
  if (!object.mesh) return;

  for (auto& triangle : object.mesh->triangles) {
    for (auto i = 0u; i < triangle.verticies.size(); ++i) {
      triangle.diffusions[i] += intensity * color * triangle.verticies[i]->color;
    }
  }
}
