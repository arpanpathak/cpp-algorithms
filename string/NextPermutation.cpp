//
// Created by Arpan Pathak on 06/11/25.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

// Data structures and containers used from the STL library...
using std::vector;
using std::swap;
using std::ranges::find_if;
using std::reverse;

vector<int> NextPermutation(vector<int> &A) {
    int k = A.size() - 2;

    // Try finding the longest increasing chain of contagious numbers from right to left.
    while (k >= 0 && A[k] >= A[k + 1]) { --k; }
    if (k == -1) {
        std::ranges::reverse(A);
        return A;
    } // This was the last lexicographically highest permutation...

    // Swap the smallest entry after index k that is greater than A[k]. We exploit the fact that
    // A[k + 1 : A.size() - 1] is decreasing, so if we search in reverse order, the first entry that is
    // greater than A[k] is smallest such entry

    swap(*find_if(A.rbegin(), A.rend(),
                  [&](int a) { return a > A[k]; })
         , A[k]);

    reverse(A.begin() + k + 1, A.end());
    return A;
}

int main() {
    vector<int> test1 = {1, 2, 3};
    vector<int> test2 = {3, 2, 1};
    vector<int> test3 = {1, 1, 5};

    std::cout << "Test 1 [1,2,3]: ";
    auto result1 = NextPermutation(test1);
    for (int x : result1) std::cout << x << " ";
    std::cout << std::endl;  // Expected: 1,3,2

    std::cout << "Test 2 [3,2,1]: ";
    auto result2 = NextPermutation(test2);
    for (int x : result2) std::cout << x << " ";
    std::cout << std::endl;  // Expected: 1,2,3

    std::cout << "Test 3 [1,1,5]: ";
    auto result3 = NextPermutation(test3);
    for (int x : result3) std::cout << x << " ";
    std::cout << std::endl;  // Expected: 1,5,1

    return 0;
}
