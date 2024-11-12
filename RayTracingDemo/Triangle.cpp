#include "Triangle.h"

Triangle::Triangle(const Vector3D& colour, const Vector3D& p0,
                   const Vector3D& p1, const Vector3D& p2)
    : Shape(colour), point1(p0), point2(p1), point3(p2) {}

bool Triangle::Intersection(const Ray& ray, double& t) {
  // Wack
  Vector3D edge1 = this->point2 - this->point1;
  Vector3D edge2 = this->point3 - this->point1;
  Vector3D perpendicular = ray.direction ^ edge2;

  double determinant = edge1 * perpendicular;
  if (aproxEqual(determinant, 0, 0.001)) return false;

  double inverseDeterminant = 1 / determinant;
  Vector3D originToVertex = ray.origin - this->point1;
  double u = inverseDeterminant * (originToVertex * perpendicular);
  if (u < 0) return false;

  Vector3D perpendicular2 = originToVertex ^ edge1;
  double v = inverseDeterminant * (ray.direction * perpendicular2);
  if (v < 0 || u + v > 1.0) return false;

  t = inverseDeterminant * (edge2 * perpendicular2);
  return t > 0;
}
