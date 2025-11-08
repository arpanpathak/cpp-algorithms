#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        const int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxPath = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                maxPath = max(maxPath, dfs(matrix, i, j, dp));
            }
        }

        return maxPath;
    }

private:
    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int dfs(const vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& dp) const {
        if (dp[i][j] != 0) return dp[i][j];

        const auto is_valid_index = [&](const int x, const int y) {
            return x >= 0 && x < matrix.size() &&
                   y >= 0 && y < matrix[0].size();
        };


        int maxLen = 1;
        for (const auto& delta : dirs) {
            int new_row = i + delta[0], new_col = j + delta[1];

            if (is_valid_index(new_row, new_col) &&
                matrix[new_row][new_col] > matrix[new_row][new_col]) {
                maxLen = max(maxLen, 1 + dfs(matrix, new_row, new_col, dp));
            }
        }

        dp[i][j] = maxLen;
        return maxLen;
    }
};
