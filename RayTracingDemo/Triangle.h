#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Ray.h"

class Triangle : public Shape
{
private:
	// Add member variables and helper functions as you see fit
	Vector3D point1;
	Vector3D point2;
	Vector3D point3;
public:
	// colour: Shape colour
	// p0: One of the three points the triangle consists of
	// p1: One of the three points the triangle consists of
	// p2: One of the three points the triangle consists of
	Triangle(const Vector3D& colour, const Vector3D& p0, const Vector3D& p1, const Vector3D& p2);

	bool Intersection(const Ray& ray, double& t) override;
};