#include <vector>
#include <algorithm>
#include <set>
#include <ranges>

using namespace std;

class RussianDollEnvelopes {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // Step 1: Sort envelopes by width ascending and height descending
        std::ranges::sort(envelopes, [](const auto &a, const auto& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1]; // Height descending when widths are equal
            }
            return a[0] < b[0]; // Width ascending
        });

        multiset<int> lis;
        
        for (const auto& envelope : envelopes) {
            int height = envelope[1];

            auto it = lis.lower_bound(height);
            if (it != lis.end()) {
                lis.erase(it);
            }

            lis.insert(height);
        }

        // The size represents the length of longest increasing subsequence
        return lis.size();
    }
};