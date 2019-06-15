#include "Cube.h"
#include "Mesh.h"

#include <vector>
#include <cassert>

#include "Vec3.h"
#include "Color.h"
#include "Vertex.h"
#include "Triangle.h"

Cube::Cube(const bool psychedelic) {
  verticies.emplace_back(Vec3f(-1,  1,  1));  // 0
  verticies.emplace_back(Vec3f(-1, -1,  1));  // 1
  verticies.emplace_back(Vec3f( 1, -1,  1));  // 2
  verticies.emplace_back(Vec3f( 1,  1,  1));  // 3
  verticies.emplace_back(Vec3f(-1,  1, -1));  // 4
  verticies.emplace_back(Vec3f(-1, -1, -1));  // 5
  verticies.emplace_back(Vec3f( 1, -1, -1));  // 6
  verticies.emplace_back(Vec3f( 1,  1, -1));  // 7

  if (psychedelic) {
    verticies[0].color = Color::CYAN;
    verticies[1].color = Color::GREEN;
    verticies[2].color = Color::YELLOW;
    verticies[3].color = Color::WHITE;
    verticies[4].color = Color::YELLOW;
    verticies[5].color = Color::WHITE;
    verticies[6].color = Color::GREEN;
    verticies[7].color = Color::CYAN;
  }

  normals.emplace_back( 1.0f,  0.0f,  0.0f);  // 0
  normals.emplace_back(-1.0f,  0.0f,  0.0f);  // 1
  normals.emplace_back( 0.0f,  1.0f,  0.0f);  // 2
  normals.emplace_back( 0.0f, -1.0f,  0.0f);  // 3
  normals.emplace_back( 0.0f,  0.0f,  1.0f);  // 4
  normals.emplace_back( 0.0f,  0.0f, -1.0f);  // 5

  triangles.emplace_back(1, 2, 3, verticies, 4, 4, 4, normals); // 0
  triangles.emplace_back(3, 0, 1, verticies, 4, 4, 4, normals); // 1
  triangles.emplace_back(6, 5, 4, verticies, 5, 5, 5, normals); // 2
  triangles.emplace_back(4, 7, 6, verticies, 5, 5, 5, normals); // 3
  triangles.emplace_back(4, 5, 1, verticies, 1, 1, 1, normals); // 4
  triangles.emplace_back(1, 0, 4, verticies, 1, 1, 1, normals); // 5
  triangles.emplace_back(3, 2, 6, verticies, 0, 0, 0, normals); // 6
  triangles.emplace_back(6, 7, 3, verticies, 0, 0, 0, normals); // 7
  triangles.emplace_back(4, 0, 3, verticies, 2, 2, 2, normals); // 8
  triangles.emplace_back(3, 7, 4, verticies, 2, 2, 2, normals); // 9
  triangles.emplace_back(1, 5, 6, verticies, 3, 3, 3, normals); // 10
  triangles.emplace_back(6, 2, 1, verticies, 3, 3, 3, normals); // 11

  assert(verticies.size() == 8u);
  assert(normals.size() == 6u);
  assert(triangles.size() == 12u);
}
