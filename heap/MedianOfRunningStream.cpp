#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class MedianFinder {
private:
    // A max-heap to store the smaller half of the numbers.
    // The top of this heap is the largest number in the smaller half.
    std::priority_queue<int> maxHeap;

    // A min-heap to store the larger half of the numbers.
    // The top of this heap is the smallest number in the larger half.
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

public:
    MedianFinder() {
        // No special initialization needed for heaps.
    }

    void addNum(int num) {
        // Add the new number to the correct heap.
        // It goes to maxHeap if it's smaller than or equal to the top of maxHeap.
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            // Otherwise, it belongs in the minHeap.
            minHeap.push(num);
        }

        // Rebalance the heaps to maintain the size invariant.
        // The maxHeap should have an equal or one greater size than the minHeap.
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() const {
        // Return the median based on the sizes of the heaps.
        // The maxHeap bears the extra element if the total count is odd.
        if (maxHeap.size() > minHeap.size()) {
            return static_cast<double>(maxHeap.top());
        }
        // If the total number of elements is even, the median is the average of the two tops.
        return static_cast<double>(maxHeap.top() + minHeap.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */