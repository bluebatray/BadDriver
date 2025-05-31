#pragma once

#include <math.h>

struct Vector3 {
  float x, y, z;

  Vector3(float xVal = 0, float yVal = 0, float zVal = 0);

  float magnitude() const;
  Vector3 normalized() const;
  float dot(const Vector3& other) const;
};
