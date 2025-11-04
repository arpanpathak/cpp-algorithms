//
// Created by Arpan Pathak on 06/09/25.
//

#include <iostream>
#include <vector>
#include <numeric>

class Solution {
public:
    int canCompleteCircuit(const std::vector<int>& gas,
        const std::vector<int>& cost) {

        int total_gas = 0, total_cost = 0;

        const auto& sum = [](const std::vector<int>& arr) {
            int total = 0;
            for (auto& x : arr) { total += x; }
            return total;
        };

        // Step 1: Check if a solution is possible
        for (int i = 0; i < gas.size(); ++i) {
            total_gas += gas[i];
            total_cost += cost[i];
        }

        if (total_gas < total_cost) {
            return -1;
        }

        // Step 2 & 3: Find the starting point greedily
        int current_gas = 0;
        int start_station = 0;

        for (int i = 0; i < gas.size(); ++i) {
            current_gas += gas[i] - cost[i];

            if (current_gas < 0) {
                // We ran out of gas. Reset the journey from the next station.
                current_gas = 0;
                start_station = i + 1;
            }
        }

        // Step 4: Return the starting station
        return start_station;
    }
};
