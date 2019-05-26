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
  explicit Mesh(const std::string& filename);

  Mesh(const Mesh& other);
  Mesh& operator=(const Mesh& other);
  Mesh(Mesh&&) = default;
  Mesh& operator=(Mesh&&) = default;
  virtual ~Mesh() = default;
private:
  // File must reside in /obj folder.
  void parse_obj_file(const std::string& filename);
};
