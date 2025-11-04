//
// Created by Arpan Pathak on 02/11/25.
//
#include <iostream>
#include <bitset>

int main() {
  std::bitset<4> flags(5);

  std::cout<<"Initial bitset ="<< flags<<std::endl;

  flags.set(2);
  std::cout << "After set(2): " << flags << std::endl; // Output: 0111

  // Access using operator[]
  flags[0] = 0; // Reset bit at index 0 (LSB) to 0
  std::cout << "After flags[0] = 0: " << flags << std::endl; // Output: 0110

  // Query
  std::cout << "Number of '1's: " << flags.count() << std::endl; // Output: 2
  std::cout << "Is bit 3 set? " << (flags.test(3) ? "Yes" : "No") << std::endl; // Output: No

  // Bitwise NOT operation
  std::bitset<4> flipped = ~flags;
  std::cout << "Flipped (NOT): " << flipped << std::endl; // Output: 1001

  return 0;
}
