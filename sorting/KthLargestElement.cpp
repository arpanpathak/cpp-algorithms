#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

using std::vector;

class Solution {
public:
    template <typename T, typename Comp>
    int quickSelectKth(vector<T>& nums, int k, Comp comp= std::less<T>()) {
        std::mt19937 gen(std::random_device{}());

        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int pivotIndex = partition(nums, left, right, comp, gen);
            if (pivotIndex == k - 1) {
                return nums[pivotIndex];
            } else if (pivotIndex < k - 1) {
                left = pivotIndex + 1;
            } else {
                right = pivotIndex - 1;
            }
        }
        return -1;
    }

private:
    template <typename T, typename Comp=std::less<T>>
    int partition(vector<T>& nums, int left, int right, Comp comp, std::mt19937& gen) {
        std::uniform_int_distribution<> dist(left, right);
        int randomIndex = dist(gen);

        std::swap(nums[randomIndex], nums[right]);

        T pivot = nums[right];
        int partitionIndex = left;

        for (int i = left; i < right; ++i) {
            // Corrected comparison: compare against the pivot value
            if (comp(nums[i], pivot)) {
                std::swap(nums[i], nums[partitionIndex++]);
            }
        }

        std::swap(nums[right], nums[partitionIndex]);
        return partitionIndex;
    }
};

int main() {
    Solution s;
    vector<int> nums = {3, 2, 1, 5, 6, 4};

    // Find the 2nd largest element using std::greater
    int k = 2;
    int result = s.quickSelectKth(nums, k, std::greater<int>());
    std::cout << "The " << k << "nd largest element is: " << result << std::endl; // Output: 5

    return 0;
}
