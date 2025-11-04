//
// Created by Arpan Pathak on 06/09/25.
//

#include <assert.h>
#include <iostream>
#include <vector>
#include <optional>

using namespace std;

optional<int> find_largest(const vector<int>& arr) {
    if (arr.empty()) return {};
    int largest = arr[0], largestIndex = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (largest < arr[i]) {
            largest = arr[i];
            largestIndex = i;
        }
    }

    return largestIndex;
}

/**
 * UNIT TEST RUNNER
 */
void testEmptyVector() {
    const vector<int>& emptyVector = {};

    assert(find_largest(emptyVector).has_value() == false);

}

void testNonEmptyVector() {
    const auto& vec = {3, 4, 6, 7, 0, -1};
    assert(find_largest(vec).has_value() == true);
    assert(find_largest(vec).value() == 7);
}

int main() {
    testEmptyVector();
    testNonEmptyVector();
}
