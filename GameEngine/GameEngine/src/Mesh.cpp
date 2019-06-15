#include "Mesh.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh::Mesh(const std::string& file_path) {
  parse_obj_file(file_path);

  // XXX: Hardcoded default vertex color value.
  for (Vertex& vertex : verticies) {
    vertex.color = Color::WHITE;
  }
}

Mesh::Mesh(const Mesh& other)
  : verticies{ other.verticies },
    normals{ other.normals } {
  triangles.reserve(other.triangles.size());
  for (const auto& other_triangle : other.triangles) {
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

auto Mesh::operator=(const Mesh& other) -> Mesh& {
  verticies = other.verticies;
  normals = other.normals;
  triangles.reserve(other.triangles.size());
  for (const auto& other_triangle : other.triangles) {
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

void Mesh::parse_obj_file(const std::string& file_path) {
  auto obj_stream = std::ifstream{ file_path };
  auto line = std::string{};

  while (std::getline(obj_stream, line)) {
    if (line.empty() || line.at(0) == '#') continue;

    auto line_stream = std::istringstream{ line };
    auto type = std::string{};
    std::getline(line_stream, type, ' ');

    if (type == "v") {
      auto position = Vec3f{};
      // TODO: Add error detection for the vertex input.
      line_stream >> position.x >> position.y >> position.z;
      verticies.emplace_back(position);

    } else if (type == "vn") {
      auto normal = Vec3f{};
      // TODO: Add error detection for the normal input.
      line_stream >> normal.x >> normal.y >> normal.z;
      normals.emplace_back(normal);

    } else if (type == "f") {
      std::vector<std::string> elements;
      { //  Scope to limit the existance of the temporary element string.
        auto element = std::string{};
        while (std::getline(line_stream, element, ' ')) {
          elements.emplace_back(element);
        }
      }

      auto position_indicies = std::vector<int>{};
      auto texture_indicies = std::vector<int>{};
      auto normal_indicies = std::vector<int>{};

      for (const std::string& element : elements) {
        auto element_stream = std::istringstream{ element };
        auto position_index = std::string{};
        auto texture_index = std::string{};
        auto normal_index = std::string{};

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
