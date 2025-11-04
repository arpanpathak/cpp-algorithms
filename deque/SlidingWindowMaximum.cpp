//
// Created by Arpan Pathak on 07/09/25.
//


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, const int k) {
    vector<int> result; result.resize(nums.size() - k);
    deque<int> dq;

    for (int i = 0; i< nums.size(); ++i) {
        // Remove outside of current window
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Remove elements smaller than current element from the back of the double ended quque
        // because these elements won't contribute to the largest element for the next window.
        // Coz those elements are useless and contribute to the max element in the current window.
        // Sliding window is all about keep computing and flushing useless carry over.
        while (!dq.empty() && nums[i] >= nums[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
        // Add current element's index to the queue....
        // Wait for window to fill threshold to start. First every window will fill at k -1 th index. Then after every
        // index move (i) will end up in a new window. So carry on computing if i >= k - 1
        if (i >= k - 1) {
            result.emplace_back(nums[dq.front()]);
        }
    }

    return result;
}
