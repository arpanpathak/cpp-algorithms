#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm> // for all_of, any_of, none_of

// For convenience and clean code, especially with ranges::views
namespace ranges = std::ranges;
namespace views = std::ranges::views;

int main() {
    // 1. Initial Data
    std::vector<int> numbers = {1, 5, 8, 12, 15, 22, 30};

    std::cout << "Original vector: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n\n";

    // --- RANGES VIEWS: MAP, FILTER, REDUCE ---

    // 2. Filter: Keep only numbers greater than 10
    //    views::filter takes a predicate (a lambda that returns a bool)
    auto filtered_view = numbers
                       | views::filter([](int n) { return n > 10; });

    std::cout << "Filter (n > 10): ";
    for (int n : filtered_view) {
        std::cout << n << " "; // Output: 12 15 22 30
    }
    std::cout << '\n';

    // 3. Map (Transform): Multiply each element by 2
    //    views::transform takes a function (a lambda that returns the new value)
    auto mapped_filtered_view = filtered_view
                              | views::transform([](int n) { return n * 2; });

    std::cout << "Map (* 2):     ";
    for (int n : mapped_filtered_view) {
        std::cout << n << " "; // Output: 24 30 44 60
    }
    std::cout << '\n';

    // 4. Reduce (Sum): Calculate the sum of the transformed elements
    //    Use std::accumulate (or ranges::fold_left in C++23)
    //    The range passed is the result of the pipeline up to this point
    int sum = std::accumulate(
        mapped_filtered_view.begin(),
        mapped_filtered_view.end(),
        0 // Initial sum value
    );
    // The C++23 way (if available):
    // int sum = ranges::fold_left(mapped_filtered_view, 0, std::plus{});

    std::cout << "Reduce (Sum):  " << sum << " (24 + 30 + 44 + 60)\n"; // Output: 158

    std::cout << "\n-------------------------------\n\n";

    // --- ALGORITHMS: all_of, any_of, none_of ---

    // These algorithms work on any range (the original vector or a generated view)

    // 5. all_of: Checks if ALL elements satisfy the condition
    bool all_over_zero = ranges::all_of(numbers, [](int n) { return n > 0; });
    std::cout << "All elements > 0? "
              << (all_over_zero ? "Yes" : "No") << '\n'; // Output: Yes

    // 6. any_of: Checks if ANY element satisfies the condition
    bool any_is_5 = ranges::any_of(numbers, [](int n) { return n == 5; });
    std::cout << "Any element is 5? "
              << (any_is_5 ? "Yes" : "No") << '\n';      // Output: Yes

    // 7. none_of: Checks if NO element satisfies the condition
    bool none_is_100 = ranges::none_of(numbers, [](int n) { return n == 100; });
    std::cout << "None element is 100? "
              << (none_is_100 ? "Yes" : "No") << '\n';  // Output: Yes

    std::cout << "\n--- Logical on Views ---\n";

    // You can also use these logical idioms on the result of a view pipeline!

    // 8. any_of on the filtered_view (12, 15, 22, 30)
    bool any_is_12 = ranges::any_of(filtered_view, [](int n) { return n == 12; });
    std::cout << "Any element in filtered_view is 12? "
              << (any_is_12 ? "Yes" : "No") << '\n'; // Output: Yes

    // 9. all_of on the mapped_filtered_view (24, 30, 44, 60)
    bool all_are_even = ranges::all_of(mapped_filtered_view, [](int n) { return n % 2 == 0; });
    std::cout << "All elements in mapped_filtered_view are even? "
              << (all_are_even ? "Yes" : "No") << '\n'; // Output: Yes

    return 0;
}
