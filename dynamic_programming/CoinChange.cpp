#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int coinChangeMin(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}

int coinChangeWays(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }

    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;

    cout << "Minimum coins: " << coinChangeMin(coins, amount) << endl;
    cout << "Number of ways: " << coinChangeWays(coins, amount) << endl;

    return 0;
}