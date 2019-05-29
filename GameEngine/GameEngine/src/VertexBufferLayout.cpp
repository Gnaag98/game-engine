#include "VertexBufferLayout.h"

#include <vector>

#include "Renderer.h"

auto VertexBufferElement::get_size_of_type(unsigned int type)->unsigned int {
  switch (type) {
    case GL_FLOAT:         return sizeof(GLfloat);
    case GL_UNSIGNED_INT:  return sizeof(GLuint);
    case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
    
    default:
      ASSERT(false);
      return 0;
  }
}

auto VertexBufferLayout::get_elements() const->const std::vector<VertexBufferElement>& {
  return m_elements;
}

auto VertexBufferLayout::get_stride() const->unsigned int {
  return m_stride;
}
