//
// Created by Arpan Pathak on 06/11/25.
//
#include <iostream>
#include <algorithm>
#include <vector>

int trap(const std::vector<int> &heights) {
    int water = 0, left = 0, right = heights.size() - 1;
    int max_left = 0, max_right = 0;

    while (left <= right) {
        max_left = std::max(max_left, heights[left]);
        max_right = std::max(max_right, heights[right]);

        water += max_left <= max_right ? (max_left - heights[left++]) : (max_right - heights[right--]);
    }

    return water;
}
