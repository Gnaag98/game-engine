#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

#include "Renderer.h"

Shader::Shader(const std::string& file_path) : m_file_path{ file_path } {
  auto source = parse_shader(file_path);
  m_renderer_id = create_shader(source.vertex_source, source.fragment_source);
}

Shader::~Shader() {
  CALL_GL(glDeleteProgram(m_renderer_id));
}

void Shader::bind() const {
  CALL_GL(glUseProgram(m_renderer_id));
}

void Shader::unbind() const {
  CALL_GL(glUseProgram(0));
}

void Shader::set_uniform1i(const std::string& name, int value) {
  CALL_GL(glUniform1i(get_uniform_location(name), value));
}

void Shader::set_uniform1f(const std::string& name, int value) {
  CALL_GL(glUniform1f(get_uniform_location(name), value));
}

void Shader::set_uniform4f(const std::string& name, int v0, int v1, int v2, int v3) {
  CALL_GL(glUniform4f(get_uniform_location(name), v0, v1, v2, v3));
}

auto Shader::parse_shader(const std::string& file_path) const->ShaderProgramSource {
  std::ifstream file_stream{ file_path };

  enum class ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  std::string line;
  // NOTE: Using std::array to do bounds checking.
  std::array<std::stringstream, 2> shader_streams;
  ShaderType type = ShaderType::NONE;

  while (std::getline(file_stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    } else if (type != ShaderType::NONE) {
      shader_streams.at(int(type)) << line << '\n';
    }
  }

  return { shader_streams.at(0).str(), shader_streams.at(1).str() };
}

auto Shader::compile_shader(unsigned int type, const std::string& source) const->unsigned int {
  CALL_GL(auto shader = glCreateShader(type));
  auto src = source.c_str();
  CALL_GL(glShaderSource(shader, 1, &src, nullptr));
  CALL_GL(glCompileShader(shader));

  auto result = GL_TRUE;
  CALL_GL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
  if (result == GL_FALSE) {
    auto length = 0;
    char message[1024];
    CALL_GL(glGetShaderInfoLog(shader, 1024, &length, message));

    std::cerr << "Failed to compile ";
    switch (type) {
      case GL_VERTEX_SHADER:
        std::cerr << "vertex";
        break;
      case GL_FRAGMENT_SHADER:
        std::cerr << "fragment";
        break;
      default:
        std::cerr << "unknown";
        break;
    }
    std::cerr << " shader!\n" << message << '\n';

    CALL_GL(glDeleteShader(shader));
    return 0;
  }

  return shader;
}

auto Shader::create_shader(const std::string& vertex_shader_source, const std::string& fragment_shader_source) const->unsigned int {
  CALL_GL(auto program = glCreateProgram());
  auto vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
  auto fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

  ASSERT(vertex_shader != 0);
  ASSERT(fragment_shader != 0);

  CALL_GL(glAttachShader(program, vertex_shader));
  CALL_GL(glAttachShader(program, fragment_shader));
  CALL_GL(glLinkProgram(program));
  CALL_GL(glValidateProgram(program));

  CALL_GL(glDeleteShader(vertex_shader));
  CALL_GL(glDeleteShader(fragment_shader));

  return program;
}

auto Shader::get_uniform_location(const std::string& name)->int {
  if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) {
    return m_uniform_location_cache[name];
  } else {
    CALL_GL(auto location = glGetUniformLocation(m_renderer_id, name.c_str()));
    if (location == -1)
      std::cerr << "Warning: uniform \"" << name << "\" doesn't exist!\n";

    m_uniform_location_cache[name] = location;
    return location;
  }
}
