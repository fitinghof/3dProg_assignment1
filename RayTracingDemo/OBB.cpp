#include "OBB.h"

OBB::OBB(const Vector3D& colour, const Vector3D& centerPoint, const Vector3D& u,
         const Vector3D& v, const Vector3D& w, double width, double height,
         double depth)
    : Shape(colour), centerPoint(centerPoint), u(u), v(v), w(w), width(width),
      height(height), depth(depth) {
    this->u.Normalize();
    this->v.Normalize();
    this->w.Normalize();
}

OBB::OBB(const Vector3D& colour, const Vector3D& centerPoint, float zRotation,
         float yRotation, float xRotation, double width, double height,
         double depth)
    : Shape(colour), centerPoint(centerPoint), u(1, 0, 0), v(0, 1, 0),
      w(0, 0, 1), width(width), height(height), depth(depth) {

    Matrix3x3 rotatedMatrix =
        Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1) *
        Matrix3x3::getRotationMatrix(zRotation, yRotation, xRotation);

    this->u = Vector3D(rotatedMatrix.at(0, 0), rotatedMatrix.at(0, 1),
                       rotatedMatrix.at(0, 2));

    this->v = Vector3D(rotatedMatrix.at(1, 0), rotatedMatrix.at(1, 1),
                       rotatedMatrix.at(1, 2));

    this->w = Vector3D(rotatedMatrix.at(2, 0), rotatedMatrix.at(2, 1),
                       rotatedMatrix.at(2, 2));
}

bool OBB::Intersection(const Ray& ray, double& t) {
    double closeIntersection = -std::numeric_limits<double>::infinity(); // tmin
    double farIntersection = std::numeric_limits<double>::infinity();    // tmax

    Vector3D rayToOBB = this->centerPoint - ray.origin; // p

    Vector3D* angleVectors[3] = {&this->u, &this->v, &this->w};
    double sizes[3] = {this->width, this->height, this->depth};

    for (int i = 0; i < 3; i++) {
        Vector3D* angleVector = angleVectors[i];
        double angleVecDotRayToOBB = *angleVector * rayToOBB;    // e
        double angleVecDotRayDir = *angleVector * ray.direction; // f

        // ray not parallel to slab
        if (!aproxEqual(angleVecDotRayDir, 0, 0.001)) {
            double currentCloseIntersection =
                (angleVecDotRayToOBB + sizes[i]) / angleVecDotRayDir;
            double currentFarIntersection =
                (angleVecDotRayToOBB - sizes[i]) / angleVecDotRayDir;

            // if far is close and close is far make far far and close close
            if (currentCloseIntersection > currentFarIntersection)
                std::swap(currentCloseIntersection, currentFarIntersection);

            // update far and close intersections to match furthes / closest
            // intersection
            if (currentCloseIntersection > closeIntersection)
                closeIntersection = currentCloseIntersection;

            if (currentFarIntersection < farIntersection)
                farIntersection = currentFarIntersection;

            // If the OBB doesn't intersect our ray or is behind us or return
            // false
            if (farIntersection < closeIntersection || farIntersection < 0)
                return false;
        }
        // incase our ray is parallel to the slabs check if it is outside of the
        // slabs
        else if (-angleVecDotRayToOBB - sizes[i] > 0 ||
                 -angleVecDotRayToOBB + sizes[i] < 0)
            return false;
    }
    // set t to the appropriate length
    if (closeIntersection > 0)
        t = closeIntersection;
    else
        t = farIntersection;

    // magicc
    return true;
}
