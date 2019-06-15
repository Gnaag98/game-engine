#include "Transform.h"

#include <iostream>
#include <utility>

const Transform Transform::ORIGIN = Transform{};

Transform::Transform() : m_position{ 0 }, m_rotation{ 0 }, m_scale{ 1 } {
  update_local_matrix();
}

Transform::Transform(Vec3f position, Vec3f rotation, Vec3f scale)
  : m_position{ position }, m_rotation{ rotation }, m_scale{ scale } {
  update_local_matrix();
}

auto Transform::local_position() const -> const Vec3f& {
  return m_position;
}

auto Transform::local_position(const Vec3f& position) -> Transform& {
  m_position = position;
  update_local_matrix();
  return *this;
}

auto Transform::local_translation_matrix() const -> Matrix44f {
  return Matrix44f::translation(m_position);
}

auto Transform::translate_locally(const Vec3f& translation) -> Transform& {
  if (m_parent) {
    m_position += std::move(translation *
                            m_parent->world_to_local_matrix().rotation_and_scale() *
                            rotation_matrix());
  } else {
    m_position += std::move(translation * rotation_matrix());
  }
  update_local_matrix();
  return *this;
}

auto Transform::position() const -> Vec3f {
  if (m_parent) {
    return std::move(m_position * m_parent->local_to_world_matrix());
  } else {
    return m_position;
  }
}

auto Transform::position(const Vec3f& position) -> Transform& {
  if (m_parent) {
    m_position = std::move(position * m_parent->world_to_local_matrix());
  } else {
    m_position = position;
  }
  update_local_matrix();
  return *this;
}

auto Transform::translation_matrix() const -> Matrix44f {
  if (m_parent) {
    return local_to_world_matrix().translation();
  } else {
    return local_translation_matrix();
  }
}

auto Transform::translate(const Vec3f& translation) -> Transform& {
  if (m_parent) {
    m_position += std::move(translation * m_parent->world_to_local_matrix().rotation_and_scale());
  } else {
    m_position += translation;
  }
  update_local_matrix();
  return *this;
}

auto Transform::local_euler_angles() const -> const Vec3f& {
  return m_rotation;
}

auto Transform::local_euler_angles(const Vec3f& angles) -> Transform& {
  m_rotation = angles;
  update_local_matrix();
  return *this;
}

auto Transform::local_rotation_matrix() const -> Matrix44f {
  return Matrix44f::rotation(m_rotation);
}

auto Transform::rotate_locally(const Vec3f& angles) -> Transform& {
  m_rotation += angles;
  update_local_matrix();
  return *this;
}

auto Transform::rotation_matrix() const -> Matrix44f {
  if (m_parent) {
    return std::move(local_rotation_matrix() * m_parent->rotation_matrix());
  } else {
    return local_rotation_matrix();
  }
}

auto Transform::local_scale() const -> const Vec3f& {
  return m_scale;
}

auto Transform::local_scale(const Vec3f& scale) -> Transform& {
  m_scale = scale;
  update_local_matrix();
  return *this;
}

auto Transform::local_matrix() const -> const Matrix44f& {
  return m_matrix;
}

auto Transform::local_to_world_matrix() const -> Matrix44f {
  if (m_parent)
    return std::move(m_matrix * m_parent->local_to_world_matrix());
  else
    return m_matrix;
}

auto Transform::world_to_local_matrix() const -> Matrix44f {
  if (m_parent)
    return local_to_world_matrix().inverse();
  else
    return m_matrix.inverse();
}

auto Transform::right() const -> Vec3f {
  return Vec3f::right() * rotation_matrix();
}

auto Transform::up() const -> Vec3f {
  return Vec3f::up() * rotation_matrix();
}

auto Transform::forward() const -> Vec3f {
  return Vec3f::forward() * rotation_matrix();
}

auto Transform::lerp_locally(const Transform& start, const Transform& end,
                                   const float percent,
                                   const bool is_translating,
                                   const bool is_rotating,
                                   const bool is_scaling) -> Transform& {
  if (is_translating) m_position.lerp(start.local_position(), end.local_position(), percent);
  if (is_rotating) m_rotation.lerp(start.local_euler_angles(), end.local_euler_angles(), percent);
  if (is_scaling) m_scale.lerp(start.local_scale(), end.local_scale(), percent);
  update_local_matrix();
  return *this;
}

void Transform::update_local_matrix() {
  m_matrix = Matrix44f{};
  if (m_scale != Vec3f{ 1 }) m_matrix.scale(m_scale.x, m_scale.y, m_scale.z);
  if (m_rotation) m_matrix.rotate(m_rotation);
  if (m_position) m_matrix.translate(m_position.x, m_position.y, m_position.z);
}