//
// Created by Arpan Pathak on 05/11/25.
//
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0;
        int n = intervals.size();

        // Add all intervals that end before newInterval starts (no overlap)
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.emplace_back(intervals[i]);
            i++;
        }

        // Merge all overlapping intervals with newInterval
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.emplace_back(newInterval);

        // Add all remaining intervals that start after newInterval ends
        while (i < n) {
            result.emplace_back(intervals[i]);
            i++;
        }

        return result;
    }
};
