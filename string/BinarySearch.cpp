//
// Created by Arpan Pathak on 06/11/25.
//

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

using namespace std;

bool search(const string& numStrs, int target) {
    auto nums = numStrs
        | views::split(' ')
        | views::transform([](auto range) { return stoi(string(range.begin(), range.end())); });


}