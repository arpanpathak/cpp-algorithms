//
// Created by Arpan Pathak on 06/09/25.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>

template <class Key, class Value>
using Map = std::unordered_map<Key, Value>;



// YaY! Baby. Let's do functional programming...

int main() {
    Map<int, int> myMap{ {1, 2}, {3, 4}};
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filter for even numbers, transform by squaring them, then print.
    auto&& result_view = numbers
                     | std::views::filter([](auto& n) { return n % 2 == 0; })
                     | std::views::transform([](auto& n) { return n * n; });

    for (const int n : result_view) {
        std::cout << n << " "; // Output: 4 16 36 64 100
    }
    std::cout << std::endl;

    // You can also pass the view directly to a range-based algorithm.
    std::vector<int> squared_evens;
    std::ranges::copy(result_view, std::back_inserter(squared_evens));

    return 0;
}
