#include "Light.h"

Light::Light() : Vertex() {}

Light::Light(const Vec3f& position) : Vertex(position) {}

Light::Light(const Vec3f& pos, const Color& col) : Vertex(pos, col) {}
