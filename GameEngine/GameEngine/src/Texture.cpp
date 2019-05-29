#include "Texture.h"

Texture::Texture(const std::vector<Color255>& frame_buffer, int width, int height)  {
  CALL_GL(glGenTextures(1, &m_renderer_id));
  CALL_GL(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

  CALL_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  CALL_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  CALL_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  CALL_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  CALL_GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer.data()));
  CALL_GL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture() {
  CALL_GL(glDeleteTextures(1, &m_renderer_id));
}

void Texture::bind(unsigned int slot) const {
  CALL_GL(glActiveTexture(GL_TEXTURE0 + slot));
  CALL_GL(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void Texture::unbind() const {
  CALL_GL(glBindTexture(GL_TEXTURE_2D, 0));
}

auto Texture::get_width() const->int {
  return 0;
}

auto Texture::get_height() const->int {
  return 0;
}
