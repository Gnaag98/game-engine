#include "VertexArray.h"

#include "Renderer.h"

VertexArray::VertexArray() {
  CALL_GL(glGenVertexArrays(1, &m_renderer_id));
}

VertexArray::~VertexArray() {
  CALL_GL(glDeleteVertexArrays(1, &m_renderer_id));
}

void VertexArray::bind() const {
  CALL_GL(glBindVertexArray(m_renderer_id));
}

void VertexArray::unbind() const {
  CALL_GL(glBindVertexArray(0));
}

void VertexArray::add_buffer(const VertexBuffer& vertex_buffer,
                             const VertexBufferLayout& layout) const {
  bind();
  vertex_buffer.bind();
  const auto& elements = layout.get_elements();
  auto offset = 0u;
  for (auto i = 0u; i < elements.size(); ++i) {
    const auto& element = elements[i];
    CALL_GL(glEnableVertexAttribArray(i));
    CALL_GL(glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                  layout.get_stride(), (const void*)offset));
    offset += element.count * VertexBufferElement::get_size_of_type(element.type);
  }
}
