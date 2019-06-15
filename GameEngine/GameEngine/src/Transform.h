#pragma once

#include "Vec3.h"
#include "Matrix44.h"

class Transform {
public:
  static const Transform ORIGIN;
  Transform* m_parent = nullptr;
private:
  Vec3f m_position;
  Vec3f m_rotation;
  Vec3f m_scale;
  Matrix44f m_matrix;

public:
  Transform();
  Transform(Vec3f position, Vec3f rotation = Vec3f{ 0 }, Vec3f scale = Vec3f{ 1 });

  [[nodiscard]]
  auto local_position() const -> const Vec3f&;
  auto local_position(const Vec3f& position) -> Transform&;
  [[nodiscard]]
  auto local_translation_matrix() const -> Matrix44f;
  auto translate_locally(const Vec3f& translation) -> Transform&;
  [[nodiscard]]
  auto position() const -> Vec3f;
  auto position(const Vec3f& position) -> Transform&;
  [[nodiscard]]
  auto translation_matrix() const -> Matrix44f;
  auto translate(const Vec3f& translation) -> Transform&;
  
  [[nodiscard]]
  auto local_euler_angles() const -> const Vec3f&;
  auto local_euler_angles(const Vec3f& euler_angles) -> Transform&;
  [[nodiscard]]
  auto local_rotation_matrix() const -> Matrix44f;
  auto rotate_locally(const Vec3f& euler_angles) -> Transform&;
  [[nodiscard]]
  auto rotation_matrix() const -> Matrix44f;
  
  [[nodiscard]]
  auto local_scale() const -> const Vec3f&;
  auto local_scale(const Vec3f& scale) -> Transform&;
  
  [[nodiscard]]
  auto local_matrix() const -> const Matrix44f&;
  [[nodiscard]]
  auto local_to_world_matrix() const -> Matrix44f;
  auto world_to_local_matrix() const -> Matrix44f;

  [[nodiscard]]
  auto right() const -> Vec3f;
  [[nodiscard]]
  auto up() const -> Vec3f;
  [[nodiscard]]
  auto forward() const -> Vec3f;

  auto lerp_locally(const Transform& start, const Transform& end,
                          float percent,
                          bool is_translating = true,
                          bool is_rotating = true,
                          bool is_scaling = true) -> Transform&;
private:
  void update_local_matrix();
};
