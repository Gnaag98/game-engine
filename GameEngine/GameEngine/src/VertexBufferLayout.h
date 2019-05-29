#pragma once

#include <vector>

#include <GL\glew.h>

struct VertexBufferElement {
  unsigned int count;
  unsigned int type;
  unsigned char normalized;

  static auto get_size_of_type(unsigned int type)->unsigned int;
};

class VertexBufferLayout {
private:
  std::vector<VertexBufferElement> m_elements;
  unsigned int m_stride = 0;

public:
  template<typename T>
  void push(const unsigned int /*count*/) {
    // Catch all unsupported types.
    static_assert(false);
  }

  template<>
  void push<float>(const unsigned int count) {
    m_elements.push_back({ count, GL_FLOAT, GL_FALSE });
    m_stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
  }

  template<>
  void push<unsigned int>(const unsigned int count) {
    m_elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
    m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
  }

  template<>
  void push<unsigned char>(const unsigned int count) {
    m_elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
    m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
  }

  [[nodiscard]] auto get_elements() const->const std::vector<VertexBufferElement>&;
  [[nodiscard]] auto get_stride() const->unsigned int;
};
