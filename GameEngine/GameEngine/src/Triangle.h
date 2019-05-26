#pragma once

#include <array>
#include <vector>

#include "Vertex.h"
#include "Color.h"

class Triangle {
public:
  std::array<Vertex*, 3> verticies;
  std::array<Vec3f*, 3> normals;
//private:
  const std::array<int, 3> vertex_indecies;
  const std::array<int, 3> normal_indecies;

public:
  //Triangle(Vertex& v_0, Vertex& v_1, Vertex& v_2);
  Triangle(int vertex_0, int vertex_1, int vertex_2, std::vector<Vertex>& verticies,
           int normal_0, int normal_1, int normal_2, std::vector<Vec3f>& normals);
  //Triangle(Vertex* vertex_0, Vertex* vertex_1, Vertex* vertex_2);
  //  Triangle is non-copyable since it contains raw pointers and can't create
  //  new verticies to point to so as to not refer to the old verticies.
  Triangle(const Triangle&) = delete;
  Triangle(Triangle&&) = default;
  Triangle& operator=(const Triangle&) = delete;
  Triangle& operator=(Triangle&&) = default;
};
