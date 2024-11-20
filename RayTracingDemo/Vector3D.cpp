#include "Vector3D.h"

Vector3D::Vector3D(double xValue, double yValue, double zValue)
    : x(xValue), y(yValue), z(zValue) {}

Vector3D Vector3D::operator+(const Vector3D& right) const {
    return Vector3D(this->x + right.x, this->y + right.y, this->z + right.z);
}

Vector3D Vector3D::operator-(const Vector3D& right) const {
    return Vector3D(this->x - right.x, this->y - right.y, this->z - right.z);
}

double Vector3D::operator*(const Vector3D& right) const {
    return this->x * right.x + this->y * right.y + this->z * right.z;
}

Vector3D Vector3D::operator^(const Vector3D& right) const {
    return Vector3D(this->y * right.z - this->z * right.y,
                    this->z * right.x - this->x * right.z,
                    this->x * right.y - this->y * right.x);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

double Vector3D::GetX() const { return this->x; }

double Vector3D::GetY() const { return this->y; }

double Vector3D::GetZ() const { return this->z; }

void Vector3D::SetX(double value) { this->x = value; }

void Vector3D::SetY(double value) { this->y = value; }

void Vector3D::SetZ(double value) { this->z = value; }

double Vector3D::Length() const { return sqrt(*this * *this); }

void Vector3D::Normalize() {
    static const double epsilon = 0.001;
    double length = this->Length();
    if (aproxEqual(length, 0, epsilon))
        return;
    this->x *= 1 / length;
    this->y *= 1 / length;
    this->z *= 1 / length;
}

void Vector3D::rotate(float z, float y, float x) {
    // rotate around z;
    float temp = this->x * cos(z) - this->y * sin(z);
    this->y = this->x * sin(z) + this->y * cos(z);
    this->x = temp;

    // rotate around y;
    temp = this->x * cos(y) + this->z * sin(y);
    this->z = -sin(y) * x + this->z * cos(y);
    this->x = temp;

    // rotate around x;
    temp = this->y * cos(x) - this->z * sin(x);
    this->z = this->y * sin(x) + this->z * cos(x);
    this->y = temp;
}
