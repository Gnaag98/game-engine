#include "Renderer.h"

#include <iostream>

void gl_clear_error() {
  while (glGetError() != GL_NO_ERROR);
}

auto gl_log_call(const char* function, const char* file, int line)->bool {
  auto is_successful = true;
  while (auto error = glGetError()) {
    std::cerr << "[OpenGL Error]\n" <<
      "  Error code: " << error << '\n' <<
      "  Function: " << function << '\n' <<
      "  File: " << file << '\n' <<
      "  Line: " << line << "\n\n";
    //return false;
    is_successful = false;
  }
  return is_successful;
}

void Renderer::clear() const {
  CALL_GL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer,
                    const Shader& shader) const {
  vertex_array.bind();
  index_buffer.bind();
  shader.bind();
  CALL_GL(glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr));

  // NOTE: Unbinding is unecessary since I'll be binding again, although good for debugging.
  vertex_array.unbind();
  index_buffer.unbind();
  shader.unbind();
}
