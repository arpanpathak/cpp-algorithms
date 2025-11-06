//
// Created by Arpan Pathak on 06/11/25.
//
#include <vector>
#include <iostream>

class NextBeautifulNumber {
public:
    int nextBeautifulNumber(int n) {
        while (true) {
            n++;
            if (isBalanced(n)) return n;
        }
    }

private:
    bool isBalanced(int num) {
        std::vector<int> count(10, 0);
        int temp = num;

        while (temp > 0) {
            count[temp % 10]++;
            temp /= 10;
        }

        for (int i = 0; i < 10; i++) {
            if (count[i] > 0 && count[i] != i) return false;
        }
        return true;
    }
};
