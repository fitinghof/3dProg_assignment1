#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Vector3D.h"

class Matrix3x3 {
  private:
    double data[3][3]; // Fixed size for 3x3 matrix

  public:
    // Default constructor: initializes all elements to zero
    Matrix3x3() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                data[i][j] = double();
    }

    // Constructor with an initializer list
    Matrix3x3(Vector3D vec1, Vector3D vec2, Vector3D vec3) {
        data[0][0] = vec1.GetX();
        data[0][1] = vec1.GetY();
        data[0][2] = vec1.GetZ();
        data[1][0] = vec2.GetX();
        data[1][1] = vec2.GetY();
        data[1][2] = vec2.GetZ();
        data[2][0] = vec3.GetX();
        data[2][1] = vec3.GetY();
        data[2][2] = vec3.GetZ();
    }

    Matrix3x3(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33) {
        data[0][0] = x11;
        data[0][1] = x12;
        data[0][2] = x13;
        data[1][0] = x21;
        data[1][1] = x22;
        data[1][2] = x23;
        data[2][0] = x31;
        data[2][1] = x32;
        data[2][2] = x33;
    }

    inline double& at(int row, int col) { return data[row][col]; }

    // Const version of at()
    const double& at(int row, int col) const {
        if (row < 0 || row >= 3 || col < 0 || col >= 3)
            throw std::out_of_range("Matrix index out of range");
        return data[row][col];
    }

    // Add two matrices
    Matrix3x3 operator+(const Matrix3x3& other) const {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Subtract two matrices
    Matrix3x3 operator-(const Matrix3x3& other) const {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    // Multiply two matrices
    Matrix3x3 operator*(const Matrix3x3& other) const {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                result.data[i][j] = double();
                for (int k = 0; k < 3; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    // Multiply Vector and Matrix
    Vector3D MatrixXVec(const Vector3D& other) {
        Vector3D result(0, 0, 0);
        result.SetX(other.GetX() * this->data[0][0] +
                    other.GetY() * this->data[0][1] +
                    other.GetZ() * this->data[0][2]);

        result.SetY(other.GetX() * this->data[1][0] +
                    other.GetY() * this->data[1][1] +
                    other.GetZ() * this->data[1][2]);

        result.SetZ(other.GetX() * this->data[2][0] +
                    other.GetY() * this->data[2][1] +
                    other.GetZ() * this->data[2][2]);

        return result;
    }

    // Transpose the matrix
    Matrix3x3 transpose() const {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.data[i][j] = data[j][i];
        return result;
    }

    // Compute the determinant of the matrix
    double determinant() const {
        return data[0][0] *
                   (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
               data[0][1] *
                   (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
               data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }

    // Print the matrix
    void print() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << std::setw(10) << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    static Matrix3x3 getRotationMatrix(float z, float y, float x) {
        const double cosX = cos(x);
        const double cosY = cos(y);
        const double cosZ = cos(z);
        const double sinX = sin(x);
        const double sinY = sin(y);
        const double sinZ = sin(z);

        return Matrix3x3(cosY * cosZ, cosZ * sinX * sinY - cosX * sinZ,
                            sinX * sinZ + cosX * cosZ * sinY, cosY * sinZ,
                            cosX * cosZ + sinX * sinY * sinZ,
                            cosX * sinY * sinZ - cosZ * sinX, -sinY,
                            cosY * sinX, cosX * cosY);
    }
};

#endif // !MATRIX_HPP