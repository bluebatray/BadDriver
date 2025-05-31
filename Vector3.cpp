#include "Vector3.hpp"

Vector3::Vector3(float xVal, float yVal, float zVal)
  : x(xVal), y(yVal), z(zVal) {}

float Vector3::magnitude() const {
  return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() const {
  float mag = magnitude();
  return (mag > 0) ? Vector3(x / mag, y / mag, z / mag) : Vector3(0, 0, 0);
}

float Vector3::dot(const Vector3& other) const {
  return x * other.x + y * other.y + z * other.z;
}
