#pragma once

#include <vector>
#include <memory>

#include "Transform.h"
#include "Animation.h"
#include "Mesh.h"

class Object {
public:
  Transform transform;
  std::unique_ptr<Animation> animation;
  std::unique_ptr<Mesh> mesh;
private:
  Object* m_parent = nullptr;
  //TODO: Add a way to own child objects so that they destruct when the parent is destroyed.

public:
  Object() = default;
  explicit Object(const Transform& transform);

  Object(const Object& other) = default;
  Object(Object&&) = default;
  Object& operator=(const Object& other) = default;
  Object& operator=(Object&&) = default;
  virtual ~Object() = default;
};
