//
// Created by Arpan Pathak on 06/11/25.
//
#include <iostream>
#include <string>

// Containers and data strucutres that I'm gonna use
using std::string;

string compressedString(string word) {
    string comp;
    for (int i = 0; i < word.size();) {
        char ch = word[i];
        int count = 0;
        while (i < word.size() && word[i] == ch && count < 9)
            count++, i++;
        comp += std::to_string(count) + ch;
    }
    return comp;
}\