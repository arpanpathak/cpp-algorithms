#include <iostream>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::istringstream;
using std::ostringstream;

vector<string> split(const string& s, const char& delim) {
    vector<string> result;
    istringstream is(s); string token;
    while (getline(is, token, delim)) {
        result.emplace_back(token);
    }
    return result;
}

// Pass by const reference for efficiency and to allow temporary objects
// to be passed in. The function does not modify its inputs.
string join(const vector<string>& vector_string, const string& delim) {
    ostringstream oss;
    for (size_t i = 0; i < vector_string.size(); i++) {
        oss << vector_string[i];
        if (i < vector_string.size() - 1) { oss << delim; }
    }
    return oss.str();
}

int main() {
    // This is the ideal way to get the result from split()
    // The compiler will use move semantics (or RVO) to avoid copying.
    auto splits = split("a#dfafasf#adsfasfm,asdas#wwww", '#');

    // You can now safely pass the `splits` vector to the `join` function.
    string delimiter = "+";
    string joined_string = join(splits, delimiter);

    std::cout << joined_string << std::endl;

    return 0;
}
