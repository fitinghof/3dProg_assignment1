#pragma once
#include <DirectXMath.h>
#include <math.h>
#include "extra.hpp"
#include <iostream>

struct Rotation {
    float z = 0;
    float y = 0;
    float x = 0;
};

class Vector3D
{
private:
	double x;
	double y;
	double z;

public:
	Vector3D(double xValue, double yValue, double zValue); // Constructor

	// Generate default implementations of all rule of five function
	~Vector3D() = default;
	Vector3D(const Vector3D& other) = default;
	Vector3D& operator=(const Vector3D& other) = default;
	Vector3D(Vector3D&& other) = default;
	Vector3D& operator=(Vector3D&& other) = default;

	Vector3D operator+(const Vector3D& right) const; // Addition
	Vector3D operator-(const Vector3D& right) const; // Subtraction
	double operator*(const Vector3D& right) const; // Dot product
	Vector3D operator^(const Vector3D& right) const; // Cross product
	Vector3D operator*(double scalar) const; // Scalar multiplication

	// Get functions for all members
	double GetX() const;
	double GetY() const;
	double GetZ() const;

		void SetX(double value);
        void SetY(double value);
        void SetZ(double value);

	double Length() const; // Return the length of the vector
	void Normalize(); // Normalize the vector

	void rotate(float z, float y, float x);
};
