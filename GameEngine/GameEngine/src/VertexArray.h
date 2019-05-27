#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
  unsigned int m_renderer_id = 0;

public:
  VertexArray();
  ~VertexArray();

  void bind() const;
  void unbind() const;

  void add_buffer(const VertexBuffer& vertex_buffer,
                  const VertexBufferLayout& layout) const;
};