//
// Created by Arpan Pathak on 01/11/25.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace line_alg {
    // Very small allowed error used for comparison purpose and tolerence...
    // 10^-12
    constexpr auto PRECISION_TOLERANCE = 1e-12;

    struct Vector2D {
        double x, y;

        auto operator+(const auto& other) const {
            return Vector2D{x + other.x, y + other.y};
        }

        auto operator-(const auto& other) const {
            return Vector2D{x - other.x, y - other.y};
        }

        auto operator==(const auto &other) const {
            return (*this - other).squaredMagnitude() < PRECISION_TOLERANCE;
        }

        double dot(const auto& other) const {
            return x * other.x + y * other.y;
        }

        double cross(const auto& other) const {
            return x *  other.y  - y * other.x;
        }

        double squaredMagnitude() const { return x * x + y * y; }
    };

    /**
     * @brief Checks if four points form a rectangle by checking:
     * 1. All angles are 90 degrees (dot product of adjacent sides is 0)
     * 2. Opposite sides are equal length
     */
    bool isRectangle(const Vector2D& p1, const Vector2D& p2,
                     const Vector2D& p3, const Vector2D& p4) {

        // Put points in a container for easier processing
        std::array<Vector2D, 4> points = {p1, p2, p3, p4};

        // Check all permutations to handle any point order
        std::array<int, 4> indices = {0, 1, 2, 3};

        do {
            const Vector2D& a = points[indices[0]];
            const Vector2D& b = points[indices[1]];
            const Vector2D& c = points[indices[2]];
            const Vector2D& d = points[indices[3]];

            // Check if this ordering forms a rectangle
            Vector2D ab = b - a;
            Vector2D bc = c - b;
            Vector2D cd = d - c;
            Vector2D da = a - d;

            // Check all angles are 90 degrees
            bool rightAngles = std::abs(ab.dot(bc)) < PRECISION_TOLERANCE &&
                             std::abs(bc.dot(cd)) < PRECISION_TOLERANCE &&
                             std::abs(cd.dot(da)) < PRECISION_TOLERANCE &&
                             std::abs(da.dot(ab)) < PRECISION_TOLERANCE;

            // Check opposite sides are equal length
            bool equalSides = std::abs(ab.squaredMagnitude() - cd.squaredMagnitude()) < PRECISION_TOLERANCE &&
                            std::abs(bc.squaredMagnitude() - da.squaredMagnitude()) < PRECISION_TOLERANCE;

            if (rightAngles && equalSides) {
                return true;
            }

        } while (std::next_permutation(indices.begin(), indices.end()));

        return false;
    }

    /**
     * @brief Alternative simpler approach using the property:
     * For a rectangle, the squared distances between all point pairs
     * should have exactly 3 distinct values (sides^2, diagonal^2, diagonal^2)
     */
    bool isRectangleSimpler(const Vector2D& p1, const Vector2D& p2,
                           const Vector2D& p3, const Vector2D& p4) {
        std::array<Vector2D, 4> points = {p1, p2, p3, p4};
        std::array<double, 6> distances;

        // Calculate squared distances between all pairs
        int idx = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                distances[idx++] = (points[i] - points[j]).squaredMagnitude();
            }
        }

        // Sort distances to find the pattern
        std::sort(distances.begin(), distances.end());

        // For a rectangle, we expect:
        // - 4 equal sides (smallest 4 distances)
        // - 2 equal diagonals (largest 2 distances)
        // - Diagonals should be twice the sides (Pythagorean theorem)
        return std::abs(distances[0] - distances[1]) < PRECISION_TOLERANCE &&
               std::abs(distances[1] - distances[2]) < PRECISION_TOLERANCE &&
               std::abs(distances[2] - distances[3]) < PRECISION_TOLERANCE &&
               std::abs(distances[4] - distances[5]) < PRECISION_TOLERANCE &&
               std::abs(distances[3] * 2 - distances[4]) < PRECISION_TOLERANCE;
    }


    struct Coordinate2D {
        double x, y;
        // DELETE: Coordinate2D(const double _x, const double _y) : x(_x), y(_y) {}
    };
    std::vector<std::vector<Coordinate2D>> coordinates = { {.x = 10.0, .y = 20.0}};
}
