#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>

std::string addBinary(std::string a, std::string b) {
    std::string result;
    int i = a.size() - 1, j = b.size() - 1, carry = 0;

    while ( i >= 0 || j >= 0 || carry ) {
        int sum = carry;
        if ( i >=0 )  sum += a[i--] - '0';
        if (j >= 0 )  sum += b[j--] - '0';
        result += ('0' + sum % 2);
        carry = sum / 2;
    }

    std::ranges::reverse(result);

    return result;
}
