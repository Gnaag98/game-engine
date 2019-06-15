#include "Light.h"

Light::Light()
  : Object{} {}

Light::Light(const Transform& t)
  : Object{ t } {}

Light::Light(const float i)
  : Object{}, intensity{ i } {}

Light::Light(const Transform& t, const float i)
  : Object{ t }, intensity{ i } {}

Light::Light(const float i, const Color& c)
  : Object{}, intensity{ i }, color{ c } {}

Light::Light(const Transform& t, const float i, const Color& c)
  : Object{ t }, intensity{ i }, color{ c } {}
