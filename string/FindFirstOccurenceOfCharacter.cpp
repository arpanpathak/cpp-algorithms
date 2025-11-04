//
// Created by Arpan Pathak on 01/11/25.
//
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> buildSuffixPrefixArray(const std::string &s) {
        std::vector<int> suffix_prefix_length(s.length(), 0);
        // len: length of previously found longest suffix which is also a prefix. i is used to iterate the string
        int len = 0 ,  i = 1;
        int m = s.length();
        if (m == 0) return suffix_prefix_length; // Handle empty string case

        while (i < m) {
            // Case 1: Characters matched (s[i] == s[len])
            if (s[i] == s[len]) {
                len++;
                suffix_prefix_length[i++] = len;
            }
            // Case of mismatch
            // If there was a previous match (len > 0), shift back using the LPS array
            else if (len != 0) {
                len = suffix_prefix_length[len - 1];
                // Do not increment i, re-check s[i] against the new s[len].
            } else {
                // Mismatch at the very start (len == 0).
                suffix_prefix_length[i++] = 0;
            }
        }
        return suffix_prefix_length;
    }

    int strStr(const std::string &haystack, const std::string &needle) {
        if (needle.length() == 0 || needle.empty()) return 0; // Empty pattern matches at index 0
        if (needle.length() > haystack.length()) return -1; // Pattern longer than text

        const auto lps = buildSuffixPrefixArray(needle);
        int i = 0, j = 0; // i for text, j for pattern

        while (i < haystack.length()) {
            if (haystack[i] == needle[j]) {
                i++; j++;
            } else if (j > 0) {
                // Mismatch with previous matches: shift pattern
                j = lps[j - 1];
            } else {
                // Mismatch at the start: advance text pointer
                i++;
            }

            // Pattern found
            if (j == needle.length()) {
                return i - j;
            }
        }

        return -1; // Not found
    }
};
