#include <iostream>
#include <string>

std::string NextNumber(std::string &s) {
    std::string result;

    for (int i = 0; i < s.length() ; ++i) {
        int count = 1;
        while ( i + 1 < s.length() && s[i] == s[i+1] ) {
            ++i; ++count;
        }
        result += std::to_string(count) + s[i];
    }

    return result;
}

std::string LookAndSay(int n) {
  std::string result = "1";
  for (int i = 1; i < n ; ++i) {
      result = NextNumber(result);
  }

  return result;
}

int main() {
  std::cout <<"n = 4 " << LookAndSay(4) << std::endl;
  return 0; 
}
