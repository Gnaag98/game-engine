#include "Transform.h"

#include <iostream>

const Transform Transform::ORIGIN = Transform{};

Transform::Transform() : m_position(0), m_rotation(0), m_scale(1) {
  std::cout << "[Transform] Default constructor.\n";
  update_matrix();
}

Transform::Transform(Vec3f pos, Vec3f rot, Vec3f scl)
  : m_position(pos), m_rotation(rot), m_scale(scl) {
  std::cout << "[Transform] Parameter constructor.\n";
  update_matrix();
}

Transform::Transform(const Transform& other)
  : m_position(other.m_position), m_rotation(other.m_rotation),
    m_scale(other.m_scale), m_matrix(other.m_matrix) {
  std::cout << "[Transform] Copy constructor.\n";
}

Transform::Transform(Transform&& other)
  : m_position(std::move(other.m_position)), m_rotation(std::move(other.m_rotation)),
  m_scale(std::move(other.m_scale)), m_matrix(std::move(other.m_matrix)) {
  std::cout << "[Transform] Move constructor.\n";
}

Transform &Transform::operator=(const Transform& other) {
  std::cout << "[Transform] Copy constructor.\n";
  m_position = other.m_position;
  m_rotation = other.m_rotation;
  m_scale = other.m_scale;
  m_matrix = other.m_matrix;
  return *this;
}

Transform &Transform::operator=(Transform&& other) {
  std::cout << "[Transform] Move constructor.\n";
  m_position = std::move(other.m_position);
  m_rotation = std::move(other.m_rotation);
  m_scale = std::move(other.m_scale);
  m_matrix = std::move(other.m_matrix);
  return *this;
}

const Vec3f& Transform::position() const {
  return m_position;
}

Transform& Transform::position(const Vec3f& position) {
  m_position = position;
  update_matrix();
  return *this;
}

Transform& Transform::translate(const Vec3f& translation) {
  m_position += translation;
  update_matrix();
  return *this;
}

const Vec3f& Transform::rotation() const {
  return m_rotation;
}

Transform& Transform::rotation(const Vec3f& rotation) {
  m_rotation = rotation;
  update_matrix();
  return *this;
}

Transform& Transform::rotate(const Vec3f& rotation) {
  m_rotation += rotation;
  update_matrix();
  return *this;
}

const Vec3f& Transform::scale() const {
  return m_scale;
}

Transform& Transform::scale(const Vec3f& scale) {
  m_scale = scale;
  update_matrix();
  return *this;
}

const Matrix44f& Transform::matrix() const {
  //std::cout << "m_position: " << m_position <<
  //  "\nm_rotation: " << m_rotation <<
  //  "\nm_scale: " << m_scale << "\n\n";
  return m_matrix;
}

Transform& Transform::lerp(const Transform& start, const Transform& end,
                           const float percent,
                           const bool is_translating,
                           const bool is_rotating,
                           const bool is_scaling) {
  //std::cout << "Lerping transform...\n";
  if (is_translating) m_position.lerp(start.position(), end.position(), percent);
  if (is_rotating) m_rotation.lerp(start.rotation(), end.rotation(), percent);
  if (is_scaling) m_scale.lerp(start.scale(), end.scale(), percent);
  update_matrix();
  //std::cout << "Done lerping transform.\n";
  return *this;
}

void Transform::update_matrix() {
  //std::cout << "Updating matrix...\n";
  m_matrix = Matrix44f();
  //std::cout << "m_matrix:\n" << m_matrix << "\n";
  if (m_rotation.z) m_matrix.rotate_z(m_rotation.z);
  //std::cout << "m_matrix:\n" << m_matrix << "\n";
  if (m_rotation.x) m_matrix.rotate_x(m_rotation.x);
  //std::cout << "m_matrix:\n" << m_matrix << "\n";
  if (m_rotation.y) m_matrix.rotate_y(m_rotation.y);
  //std::cout << "m_matrix:\n" << m_matrix << "\n";
  if (m_position)   m_matrix.translate(m_position.x, m_position.y, m_position.z);
  //std::cout << "m_matrix:\n" << m_matrix << "\n";
  if (m_scale != Vec3f(1)) m_matrix.scale(m_scale.x, m_scale.y, m_scale.z);
  //std::cout << "m_matrix:\n" << m_matrix << "\n";
  //std::cout << "Done updating matrix.\n";
}