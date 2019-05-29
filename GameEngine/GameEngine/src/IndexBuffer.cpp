#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(unsigned int* const data, const unsigned int count) 
  : m_count{ count } {
  // Using c++ datatypes so I need to compare their size to OpenGL datatypes.
  ASSERT(sizeof(unsigned int) == sizeof(GLuint));

  CALL_GL(glGenBuffers(1, &m_renderer_id));
  CALL_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
  CALL_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
  CALL_GL(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::bind() const {
  CALL_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::unbind() const {
  CALL_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

auto IndexBuffer::get_count() const->unsigned int {
  return m_count;
}
