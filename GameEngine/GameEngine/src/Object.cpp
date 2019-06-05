#include "Object.h"

#include <memory>

#include "Transform.h"
#include "Mesh.h"

Object::Object(const Transform& _transform) : transform(_transform) {}
