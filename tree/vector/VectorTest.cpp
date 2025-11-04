//
// Created by Arpan Pathak on 03/09/25.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 8, 2, 4, 5};


    std::sort(v.begin(), v.end(), [](auto &x, auto &y) {  return x < y; });

    stringstream ss;
    for (auto &x : v) { ss<< x <<","; }

    cout << ss.str() << endl;

    return 0;
}