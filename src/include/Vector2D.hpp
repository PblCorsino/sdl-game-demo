#ifndef __VECTOR2D__
#define __VECTOR2D__

#include<math.h>

/*
  Class for vector operations in 2d
*/
class Vector2D {

public:
  Vector2D(float x, float y);

  float getX() const;
  float getY() const;
  float length() const;
  void normalize();

  Vector2D operator+(const Vector2D& v2) const; 
  friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2); 
  Vector2D operator*(float scalar);
  Vector2D& operator*=(float scalar);
  Vector2D operator-(const Vector2D& v2) const; 
  friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2); 
  Vector2D operator/(float scalar);
  Vector2D& operator/=(float scalar);

  void setX(float x);
  void setY(float y);

private:

  float m_x;
  float m_y;
};

#endif
