#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define CALL_GL(x) gl_clear_error();\
  x;\
  ASSERT(gl_log_call(#x, __FILE__, __LINE__))

void gl_clear_error();
auto gl_log_call(const char* function, const char* file, int line)->bool;

class Renderer {
public:
  void clear() const;
  void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer,
            const Shader& shader) const;
};
