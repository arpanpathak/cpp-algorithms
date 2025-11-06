//
// Created by Arpan Pathak on 06/11/25.
//
#include <iostream>
#include <vector>

enum Color {
    RED = 0, WHITE = 1, BLUE = 2
};

void sortColors(std::vector<Color> &colors) {
    int low = 0, high = colors.size() - 1, i = 0;

    while ( i <= high) {
        if (colors[i] == RED) { std::swap(colors[i++], colors[low++]); }
        else if (colors[i] == WHITE) { i++; }
        else if (colors[i] == BLUE) { std::swap(colors[i], colors[high--]); }
    }
}

int main() {

    std::vector<Color> colors { RED, BLUE, BLUE, WHITE, RED, RED, BLUE, WHITE };
    sortColors(colors);

    for (const auto& color : colors) {
        std::cout << color << std::endl;
    }
    return 0;
}
