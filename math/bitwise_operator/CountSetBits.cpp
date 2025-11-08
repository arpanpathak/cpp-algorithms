//
// Created by Arpan Pathak on 06/11/25.
//
#include <iostream>

int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }

    return count;
}

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n-1)) == 0;
}

int lowestSetBit(int n) {
    return n & -n; // -n is same as ~
}

// Or get the position (0-indexed from right)
int lowestSetBitPosition(int n) {
    return __builtin_ctz(n);  // Count trailing zeros
}

int clearLowestSetBit(int n) {
    return n & (n-1);
}

int main() {
    std::cout << countSetBits(3) << std::endl;
    std::cout << "Ones completement of 5 = " << ~5 << std::endl;
    std::cout << "Twos complement of 5 = " << ~(5 -1); // ~ is ones complement....
    return 0;
}
