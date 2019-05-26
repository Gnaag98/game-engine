#pragma once

#include "Vec3.h"
#include "Matrix44.h"

class Transform {
public:
  static const Transform ORIGIN;
  static int i;
private:
  Vec3f m_position;
  Vec3f m_rotation;
  Vec3f m_scale;
  Matrix44f m_matrix;
  // TODO: Add parent transform.

public:
  Transform();
  Transform(Vec3f position, Vec3f rotation = Vec3f(0), Vec3f scale = Vec3f(1));
  Transform(const Transform& other);
  Transform(Transform&& other);
  Transform& operator=(const Transform& other);
  Transform& operator=(Transform&& other);

  const Vec3f& position() const;
  Transform& position(const Vec3f& position);
  Transform& translate(const Vec3f& translation);

  const Vec3f& rotation() const;
  Transform& rotation(const Vec3f& rotation);
  Transform& rotate(const Vec3f& rotation);
  
  const Vec3f& scale() const;
  Transform& scale(const Vec3f& scale);

  const Matrix44f& matrix() const;

  Transform& lerp(const Transform& start, const Transform& end,
                  float percent,
                  bool is_translating = true,
                  bool is_rotating = true,
                  bool is_scaling = true);
private:
  void update_matrix();
};
