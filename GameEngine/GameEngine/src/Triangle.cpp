#include "Triangle.h"

#include <array>

#include "Vertex.h"
#include "Color.h"

Triangle::Triangle(int v_0, int v_1, int v_2, std::vector<Vertex>& _verticies,
                   int n_0, int n_1, int n_2, std::vector<Vec3f>& _normals)
  : verticies{ &_verticies.at(v_0), &_verticies.at(v_1), &_verticies.at(v_2) },
    vertex_indecies{v_0, v_1, v_2},
    normals{ &_normals.at(n_0), &_normals.at(n_1), &_normals.at(n_2) },
    normal_indecies{ n_0, n_1, n_2 } {}
