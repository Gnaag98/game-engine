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
  // TODO: implement logic for objects having children and/or parents.
  //std::vector<Object> children;
  std::shared_ptr<Mesh> mesh;

public:
  Object() = default;
  explicit Object(const Transform& transform);
  Object(const Transform& transform, std::shared_ptr<Mesh> mesh);

  Object(const Object& other) = default;
  Object(Object&&) = default;
  Object& operator=(const Object& other) = default;
  Object& operator=(Object&&) = default;
  virtual ~Object() = default;
};
