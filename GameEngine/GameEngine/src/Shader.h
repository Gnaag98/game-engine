#pragma once

#include <string>
#include <unordered_map>

class Shader {
private:
  struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
  };

private:
  // Save file path for debugging purposes.
  const std::string m_file_path;
  unsigned int m_renderer_id = 0;
  // Make the cache mutable so that the rest of the class can be marked const.
  std::unordered_map<std::string, int> m_uniform_location_cache;

public:
  explicit Shader(const std::string& file_path);
  ~Shader();

  void bind() const;
  void unbind() const;

  void set_uniform1i(const std::string& name, int value);
  void set_uniform1f(const std::string& name, float value);
  void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
  auto parse_shader(const std::string& file_path) const->ShaderProgramSource;
  auto compile_shader(unsigned int type, const std::string& source) const->unsigned int;
  auto create_shader(const std::string& vertex_shader_source,
                     const std::string& fragment_shader_source) const->unsigned int;
  auto get_uniform_location(const std::string& name)->int;
};
