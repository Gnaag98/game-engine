#include "Vertex.h"

#include "Vec3.h"
#include "Color.h"

Vertex::Vertex() {}

Vertex::Vertex(const Vec3f& p) : position(p), color(Color::WHITE) {}

Vertex::Vertex(const Vec3f& p, const Color& c) : position(p), color(c) {}
