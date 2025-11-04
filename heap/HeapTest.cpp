//
// Created by Arpan Pathak on 04/09/25.
//
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    auto cmp = [](const int& a, const int& b) { return a > b; }; // min-heap comparator
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(2);

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }

    return 0;
}