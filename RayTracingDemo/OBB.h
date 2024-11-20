#pragma once

#include "Ray.h"
#include "Shape.h"
#include "Vector3D.h"
#include "extra.hpp"
#include "Matrix.hpp"

class OBB : public Shape {
  private:
    // Add member variables and helper functions as you see fit
    Vector3D u, v, w;
    Vector3D centerPoint;
    double width, height, depth;

  public:
    // colour: Shape colour
    // centerPoint: Point at which the OBB center lies
    // u: Directional vector for indicating orientation of the OBB
    // v: Directional vector for indicating orientation of the OBB
    // w: Directional vector for indicating orientation of the OBB
    // width: Distance from center to side in the u-axis of the OBB
    // height: Distance from center to side in the v-axis of the OBB
    // depth: Distance from center to side in the w-axis of the OBB
    OBB(const Vector3D& colour, const Vector3D& centerPoint, const Vector3D& u,
        const Vector3D& v, const Vector3D& w, double width, double height,
        double depth);

    OBB(const Vector3D& colour, const Vector3D& centerPoint, float zRotation,
        float yRotation, float xRotation, double width, double height,
        double depth);

    bool Intersection(const Ray& ray, double& t) override;
};