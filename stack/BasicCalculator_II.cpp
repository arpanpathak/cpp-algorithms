//
// Created by Arpan Pathak on 06/11/25.
//
#include <string>
#include <vector>
#include <cctype>

int calculate(const std::string& s) {
    // Using vector as stack because we need to immediately perform multiplication operation
    std::vector<int> stack;
    int currentNumber = 0;
    char operation = '+';

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];

        if (std::isdigit(c)) {
            currentNumber = currentNumber * 10 + (c - '0');
        }

        if ((!std::isdigit(c) && c != ' ') || i == s.length() - 1) {
            switch (operation) {
                case '+':
                    stack.push_back(currentNumber);
                    break;
                case '-':
                    stack.push_back(-currentNumber);
                    break;
                case '*':
                    stack.back() *= currentNumber;
                    break;
                case '/':
                    stack.back() /= currentNumber;
                    break;
            }
            operation = c;
            currentNumber = 0;
        }
    }

    int sum = 0;
    for (int num : stack) {
        sum += num;
    }
    return sum;
}