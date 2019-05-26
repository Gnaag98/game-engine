#include "Object.h"

#include <memory>

#include "Transform.h"
#include "Mesh.h"

Object::Object(const Transform& _transform) : transform(_transform) {}

Object::Object(const Transform& _transform, std::shared_ptr<Mesh> _mesh)
  : transform(_transform), mesh(std::move(_mesh)) {}
