#pragma once

class IndexBuffer {
private:
  unsigned int m_renderer_id = 0;
  unsigned int m_count;

public:
  IndexBuffer(unsigned int* const data, const unsigned int count);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  [[nodiscard]] auto get_count() const->unsigned int;
};