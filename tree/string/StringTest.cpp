//
// Created by Arpan Pathak on 28/08/25.
//
#include <assert.h>
#include <format>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    string s = "thisisastringtest";
    string raw = R"(
        {
          "name": "Bob",
          "peter": 233,
          "age": 25,
          "isStudent
          ": true
        })";

    cout << s.rfind("ing");
    cout << s.substr(10, 3);
    const auto& xxx = R"(
        This is a fucking multiline string, Ouuuu Yeah!
    )";

    set<int> ws;
    return 0;
}
