#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <utility> 

struct Star {
    int x, y, z;

    int getSquaredDistance() const {
        return x * x + y * y + z * z;
    }
    
    Star() : x(0), y(0), z(0) {}
    Star(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

class KClosestStars {
private:
    int partition(std::vector<Star>& stars, int start, int end) {
        static std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<> distrib(start, end);
        int randomIndex = distrib(gen);

        std::swap(stars[end], stars[randomIndex]); 
        
        int partitionIndex = start;
        int pivotDistance = stars[end].getSquaredDistance();

        for (int i = start; i < end; ++i) {
            int currentDistance = stars[i].getSquaredDistance();
            if (currentDistance <= pivotDistance) {
                std::swap(stars[i], stars[partitionIndex]);
                partitionIndex++;
            }
        }

        std::swap(stars[partitionIndex], stars[end]);
        return partitionIndex;
    }

public:
    std::vector<Star> kClosest(std::vector<Star>& stars, int K) {
        if (K <= 0 || stars.empty()) {
            return {};
        }

        int start = 0, end = stars.size() - 1;
        const int targetIndex = K - 1;

        while (start < end) {
            int pivotIndex = partition(stars, start, end);
            
            if (pivotIndex < targetIndex) {
                start = pivotIndex + 1;
            } else if (pivotIndex > targetIndex) {
                end = pivotIndex - 1;
            } else {
                break; // We found partition index == targetIndex 
            }
        }

        return std::vector<Star>(stars.begin(), stars.begin() + K);
    }
};

// --- Example Usage ---

int main() {
    std::vector<Star> celestialBodies = {
        Star(1, 1, 1),
        Star(0, 0, 5),
        Star(-1, 2, 2),
        Star(3, 1, 0),
        Star(0, 1, 0)
    };
    int K = 3;

    KClosestStars solver;
    std::vector<Star> closestStars = solver.kClosest(celestialBodies, K);

    std::cout << "K=" << K << " Closest Stars (C++ final):\n";
    for (const auto& star : closestStars) {
        std::cout << "Star (" << star.x << ", " << star.y << ", " << star.z << ") -> Dist^2: " << star.getSquaredDistance() << "\n";
    }

    return 0;
}