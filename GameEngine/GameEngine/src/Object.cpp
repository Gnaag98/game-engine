#include "Object.h"

#include <memory>

#include "Transform.h"
#include "Mesh.h"

Object::Object(const Transform& _transform) : transform(_transform) {}

auto Object::parent() const -> Object* {
  return m_parent;
}

auto Object::parent(Object* parent) -> Object& {
  if (!parent) return *this;
  m_parent = parent;
  transform.m_parent = &parent->transform;
  return *this;
}
