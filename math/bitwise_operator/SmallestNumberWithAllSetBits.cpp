//
// Created by Arpan Pathak on 06/11/25.
//

int smallestNumber(int n) {
    if (n <= 1) return 1;

    // Find the bit position of the most significant set bit
    int msb = 0;
    while ((1 << msb) <= n) {
        msb++;
    }

    // The number with all bits set up to msb position is (1 << msb) - 1
    return (1 << msb) - 1;
}
