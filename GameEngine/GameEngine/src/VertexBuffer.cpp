#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const unsigned int size, const void* const data) {
  CALL_GL(glGenBuffers(1, &m_renderer_id));
  CALL_GL(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
  CALL_GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  CALL_GL(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::bind() const {
  CALL_GL(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::unbind() const {
  CALL_GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
