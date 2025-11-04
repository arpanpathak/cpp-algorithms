#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>

class DualSword {
private:
    std::priority_queue<int> max_heap; 
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    std::unordered_map<int, int> to_be_removed;

    void rebalance() {
        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    void clean_heaps() {
        while (!max_heap.empty() && to_be_removed[max_heap.top()] > 0) {
            to_be_removed[max_heap.top()]--;
            max_heap.pop();
        }
        while (!min_heap.empty() && to_be_removed[min_heap.top()] > 0) {
            to_be_removed[min_heap.top()]--;
            min_heap.pop();
        }
    }

public:
    void insert(int num) {
        if (max_heap.empty() || num <= max_heap.top()) {
            max_heap.push(num);
        } else {
            min_heap.push(num);
        }
        rebalance();
    }

    void remove(int num) {
        to_be_removed[num]++;
    }

    double get_median() {
        clean_heaps();
        if (max_heap.size() == min_heap.size()) {
            return (static_cast<double>(max_heap.top()) + min_heap.top()) / 2.0;
        } else {
            return static_cast<double>(max_heap.top());
        }
    }
};

class Solution {
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        std::vector<double> result;
        DualSword ds;

        for (int i = 0; i < nums.size(); ++i) {
            // Insert the current element
            ds.insert(nums[i]);

            // Once the window is full, remove the oldest element
            if (i >= k) {
                ds.remove(nums[i - k]);
            }
            
            // Record the median once the window is full
            if (i >= k - 1) {
                result.push_back(ds.get_median());
            }
        }
        return result;
    }
};