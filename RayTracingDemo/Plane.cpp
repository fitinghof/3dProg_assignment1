#include "Plane.h"

Plane::Plane(const Vector3D& colour, const Vector3D& p, const Vector3D& n)
	: Shape(colour), point(p), normal(n)
{}

bool Plane::Intersection(const Ray& ray, double& t)
{
	// Implement intersection logic here
	// Prob basicly a distance multiplyer (but divider) based on how parallel the ray is to the plane
	double denom = (ray.direction) * (this->normal);

	if (aproxEqual(denom, 0, 0.001)) return false;

	Vector3D rayToPlaneVector = this->point - ray.origin;

	t = (rayToPlaneVector * this->normal) / denom;

	return (t > 0);
}
