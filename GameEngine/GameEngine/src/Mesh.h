#pragma once

#include <vector>
#include <string>

#include "Vec3.h"
#include "Vertex.h"
#include "Triangle.h"

class Mesh {
public:
  std::vector<Vertex> verticies;
  std::vector<Vec3f> normals;
  std::vector<Triangle> triangles;

public:
  Mesh() = default;
  explicit Mesh(const std::string& file_path);
  Mesh(const Mesh& other);
  auto operator=(const Mesh& other) -> Mesh&;
  Mesh(Mesh&&) = default;
  auto operator=(Mesh&&) -> Mesh& = default;
  virtual ~Mesh() = default;
private:
  void parse_obj_file(const std::string& file_path);
};
