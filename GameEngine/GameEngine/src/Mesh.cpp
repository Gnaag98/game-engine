#include "Mesh.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh::Mesh(const std::string& filename) {
  parse_obj_file(filename);

  // XXX: Hardcoded vertex color value.
  for (Vertex& vertex : verticies) {
    vertex.color = Color::WHITE;
  }
}

Mesh::Mesh(const Mesh& other)
  : verticies(other.verticies),
    normals(other.normals) {
  triangles.reserve(other.triangles.size());
  for (const Triangle& other_triangle : other.triangles) {
    triangles.emplace_back(other_triangle.vertex_indecies[0],
                           other_triangle.vertex_indecies[1],
                           other_triangle.vertex_indecies[2],
                           verticies,
                           other_triangle.normal_indecies[0],
                           other_triangle.normal_indecies[1],
                           other_triangle.normal_indecies[2],
                           normals);
  }
}

Mesh& Mesh::operator=(const Mesh& other) {
  verticies = other.verticies;
  normals = other.normals;
  triangles.reserve(other.triangles.size());
  for (const Triangle& other_triangle : other.triangles) {
    triangles.emplace_back(other_triangle.vertex_indecies[0],
                           other_triangle.vertex_indecies[1],
                           other_triangle.vertex_indecies[2],
                           verticies,
                           other_triangle.normal_indecies[0],
                           other_triangle.normal_indecies[1],
                           other_triangle.normal_indecies[2],
                           normals);
  }
  return *this;
}

// File must reside in /obj folder.
void Mesh::parse_obj_file(const std::string& filename) {
  std::ifstream obj_stream(std::string("obj/") + filename + ".obj");
  std::string line;

  while (std::getline(obj_stream, line)) {
    if (line.empty() || line.at(0) == '#') continue;

    std::istringstream line_stream(line);
    std::string type;
    std::getline(line_stream, type, ' ');

    if (type == "v") {
      Vec3f position;
      // TODO: Add error detection for the vertex input.
      line_stream >> position.x >> position.y >> position.z;
      verticies.emplace_back(position);

    } else if (type == "vn") {
      Vec3f normal;
      // TODO: Add error detection for the normal input.
      line_stream >> normal.x >> normal.y >> normal.z;
      normals.emplace_back(normal);

    } else if (type == "f") {
      std::vector<std::string> elements;
      { //  Scope to limit the existance of the temporary element string.
        std::string element;
        while (std::getline(line_stream, element, ' ')) {
          elements.emplace_back(element);
        }
      }

      std::vector<int> position_indicies;
      std::vector<int> texture_indicies;
      std::vector<int> normal_indicies;

      for (const std::string& element : elements) {
        std::istringstream element_stream(element);
        std::string position_index;
        std::string texture_index;
        std::string normal_index;
        std::getline(element_stream, position_index, '/');
        std::getline(element_stream, texture_index, '/');
        std::getline(element_stream, normal_index, '/');
        // Converting to 0 based indexing by subtracting by 1.
        position_indicies.emplace_back(std::stoi(position_index) - 1);
        texture_indicies.emplace_back(std::stoi(texture_index) - 1);
        normal_indicies.emplace_back(std::stoi(normal_index) - 1);
      }

      if (position_indicies.size() < 3) {
        throw std::runtime_error("Need at least 3 verticies to create a face.");
      }

      triangles.emplace_back(position_indicies[0],
                             position_indicies[1],
                             position_indicies[2],
                             verticies,
                             normal_indicies[0],
                             normal_indicies[1],
                             normal_indicies[2],
                             normals);

      // Create a second triangle if the face was a quad.
      if (position_indicies.size() == 4) {
        triangles.emplace_back(position_indicies[2],
                               position_indicies[3],
                               position_indicies[0],
                               verticies,
                               normal_indicies[2],
                               normal_indicies[3],
                               normal_indicies[0],
                               normals);
      }
    }
  }
}
