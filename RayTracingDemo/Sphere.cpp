#include "Sphere.h"

#include <cmath>

Sphere::Sphere(const Vector3D& colour, const Vector3D c, double r)
	: Shape(colour), centerPoint(c), radius(r)
{}

bool Sphere::Intersection(const Ray& ray, double& t)
{

	// Allt borde döpas om men jag vet inte hur jag ska döpa skiten bra, allt känns wack

	Vector3D rayToSphere = this->centerPoint - ray.origin;

	// ..centerLine is some imaginary line that goes 90 degrees out from the sphere center from
	// the rayToSphere's vectors point of view
	double LengthFromRayToSphereCenterLine = rayToSphere * ray.direction;

	double radiusSquared = this->radius * this->radius;

	// Note, "(rayToSphere * rayToSphere) > (this->radius * this->radius)"
	// would be "rayToSphere.Length() > this->radius" but to avoid the sqrt() in .Length()
	// we instead compare the two squared numbers as this will yield the same result.
	// "distanceFromRayToSphereCenter < 0" indicates if we are infront of the sphere
	if (LengthFromRayToSphereCenterLine < 0 && (rayToSphere * rayToSphere) >(radiusSquared))
		return false;

	double ShortesLengthFromRayToSphereCenterSquared = 
		rayToSphere * rayToSphere - LengthFromRayToSphereCenterLine * LengthFromRayToSphereCenterLine;

	// if the ray passes the entire sphere
	if (ShortesLengthFromRayToSphereCenterSquared > radiusSquared)
		return false;

	double centerLineToSphereEdge = sqrt(radiusSquared - ShortesLengthFromRayToSphereCenterSquared);

	t = LengthFromRayToSphereCenterLine - centerLineToSphereEdge;

	return true;
}