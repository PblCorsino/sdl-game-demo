#include"include/Vector2D.hpp"

Vector2D::Vector2D(float x, float y)
{
  m_x = x;
  m_y = y;
}

float Vector2D::getX() const {
  return m_x;
}

float Vector2D::getY() const {
  return m_y;
}

float Vector2D::length() const {
  return sqrt((m_x * m_x) + (m_y * m_y));
}

/*
  Normalize a vector make its length equal to 1
  Vectors with a lenght of 1 are known as unit vectors and are useful to represent a direction
*/
void Vector2D::normalize() {
  float l = length();
  // To normalize a vector, whe need to multiply it by the inverse of its length
  // When its lenght is greater than zero
  if ( l > 0 ) {
    (*this) *= 1 / l;
  }
}

Vector2D Vector2D::operator+(const Vector2D& v2) const {
  return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

// Friend functions are not members of the class
Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
  v1.m_x += v2.m_x;
  v1.m_y += v2.m_y;

  return v1;
}

Vector2D Vector2D::operator*(float scalar) {
  return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D& Vector2D::operator*=(float scalar) {
  m_x *= scalar;
  m_y *= scalar;

  return *this;
}

Vector2D Vector2D::operator-(const Vector2D& v2) const {
  return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

// Friend functions are not members of the class
Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
  v1.m_x -= v2.m_x;
  v1.m_y -= v2.m_y;

  return v1;
}

Vector2D Vector2D::operator/(float scalar) {
  return Vector2D(m_x / scalar, m_y / scalar);
}

Vector2D& Vector2D::operator/=(float scalar) {
  m_x /= scalar;
  m_y /= scalar;

  return *this;
}

void Vector2D::setX(float x) {
  m_x = x;
}

void Vector2D::setY(float y) {
  m_y = y;
}
