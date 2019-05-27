#pragma once

class VertexBuffer {
private:
  unsigned int m_renderer_id = 0;

public:
  VertexBuffer(const unsigned int size, const void* const data);
  ~VertexBuffer();

  void bind() const;
  void unbind() const;
};
