#include <cstdint>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Disc.h"
#include "Matrix.hpp"
#include "OBB.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "stb_image_write.h"

int main() {
    const unsigned int width = 512;
    const unsigned int height = 512;
    const int channels = 3;
    // uint8_t = unsigned integer type consisting of 8 bits, often just unsigned
    // char in the background
    uint8_t* imageData = new uint8_t[width * height * channels];

    Shape* shapes[]{
        new Triangle(Vector3D(255, 0, 0), Vector3D(-128, 250, 16),
                     Vector3D(128, 250, -16), Vector3D(0, -250, -100)),
        new Sphere(Vector3D(0, 200, 200), Vector3D(0, 0, 256 - 256), 128),
        new OBB(Vector3D(0, 0, 250), Vector3D(150, -64, 0), 45, 45, 45, 100,
                100, 100),
        new Plane(Vector3D(0, 255, 0), Vector3D(0, 0, 50), Vector3D(0, 0, 1)),
    };

    double* distances = new double[width * height];
    std::fill(&distances[0], &distances[0] + width * height,
              std::numeric_limits<double>::infinity());

    Vector3D cameraPos(0, 0, -256);

    Rotation cameraRotation{0 * PI, 0 * PI, 0 * PI};

    Matrix3x3 camRotationMatrix = Matrix3x3::getRotationMatrix(
        cameraRotation.x, cameraRotation.y, cameraRotation.z);

    cameraPos = camRotationMatrix.MatrixXVec(cameraPos);

    Vector3D cameraDirection = camRotationMatrix.MatrixXVec(Vector3D(0, 0, 1));

    double maxDistance = -std::numeric_limits<double>::infinity();
    double minDistance = std::numeric_limits<double>::infinity();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector3D rayOrigin = camRotationMatrix.MatrixXVec(Vector3D(
                                     ((double)x - (double)width / 2),
                                     ((double)height / 2 - (double)y), 0)) +
                                 cameraPos;
            double distance = -1;
            for (Shape* shape : shapes) {
                if (shape->Intersection(Ray(rayOrigin, cameraDirection),
                                        distance)) {
                    if (distance < distances[y * width + x]) {
                        distances[y * width + x] = distance;
                        Vector3D colour = shape->GetColour();
                        imageData[(y * width + x) * channels] =
                            static_cast<uint8_t>(colour.GetX());
                        imageData[(y * width + x) * channels + 1] =
                            static_cast<uint8_t>(colour.GetY());
                        imageData[(y * width + x) * channels + 2] =
                            static_cast<uint8_t>(colour.GetZ());
                    }
                }
            }
            // Set max and min distances for grading
            if (distance != -1) {
                if (distances[y * width + x] < minDistance)
                    minDistance = distances[y * width + x];
                if (distances[y * width + x] > maxDistance)
                    maxDistance = distances[y * width + x];
            }
        }
    }
    std::cout << minDistance << " " << maxDistance << "\n";

    double minColorMultiplier = 0.3;
    // Adds a simple gradient
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double normalizedDistance =
                (distances[y * width + x] - minDistance) /
                (maxDistance - minDistance);
            double colourMultiplier =
                (1 - minColorMultiplier) * (1 - normalizedDistance) +
                minColorMultiplier;
            imageData[(y * width + x) * channels] *= colourMultiplier;
            imageData[(y * width + x) * channels + 1] *= colourMultiplier;
            imageData[(y * width + x) * channels + 2] *= colourMultiplier;
        }
    }

    // This is the main function in which you should create shapes and use them
    // to ray trace a simple scene containing the shapes It is ok to create
    // helper functions and utelize them Make sure that you pass all of the
    // automatic tests before implementing this part

    // To switch which main function is being used, exclude either this file
    // from the build, or all the test files Right click file, properties,
    // configuration properties, general, exclude from build = Yes/No

    stbi_write_png("Traced.png", width, height, channels, imageData,
                   width * channels);
    delete[] imageData;
    delete[] distances;

    for (Shape* shape : shapes) {
        delete shape;
    }
    // system("pause");
    return 0;
}