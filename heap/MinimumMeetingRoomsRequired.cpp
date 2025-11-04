//
// Created by Arpan Pathak on 02/11/25.
//
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <iostream>
#import <ranges>

// Helper Functions and namespaces
using std::ranges::sort;

class Solution {
public:
    int minMeetingRooms(std::vector<std::vector<int>>&& intervals) {

        // 1. Sort the intervals by their start time (interval[0]).
        // Using 'auto' for the lambda parameters makes the code cleaner.
        sort(intervals,[](const auto& a, const auto& b) {
            return a[0] < b[0];
        });

        // 2. Initialize a Min-Heap (Priority Queue) to store meeting end times.
        // It's declared concisely here.
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        // 3. Iterate through the sorted intervals.
        for (const auto& interval : intervals) {
            // If the current meeting starts after or exactly when the earliest active meeting ends.
            if (!min_heap.empty() && interval[0] >= min_heap.top()) {
                // Reuse the room: remove the earliest end time.
                min_heap.pop();
            }

            // Occupy the room by adding the current meeting's end time.
            min_heap.push(interval[1]);
        }

        // The size of the heap is the maximum overlap (minimum rooms required).
        return min_heap.size();
    }
};

int main() {
    Solution s;
    int minMeetings = s.minMeetingRooms({{2,6}, {3,6}, {1,2}});

    std::cout << minMeetings << std::endl;


    return 0;
}
