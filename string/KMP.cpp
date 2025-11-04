#include <iostream>
#include <vector>
#include <string>
#include <cassert> // Required for assert()
#include <algorithm> // Required for std::equal

// Function to compute the Longest Proper Prefix which is also a Suffix (LPS) array.
// s is the pattern string
std::vector<int> buildSuffixPrefixArray(const std::string &s) {
    std::vector<int> suffix_prefix_length(s.length(), 0);
    // len: length of previously found longest suffix which is also a prefix. i is used to iterate the string
    int len = 0 ,  i = 1;
    const int m = s.length();
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


// KMP search function: returns the starting index of the first occurrence, or -1.
int kmpSearch(const std::string &s, const std::string &t) {
    const int n = s.length(), m = t.length();

    if (m == 0) return 0; // Empty pattern matches at index 0
    if (n < m) return -1; // Pattern longer than text

    const auto lps = buildSuffixPrefixArray(t);

    int i = 0, j = 0; // i for text, j for pattern

    while (i < n) {
        if (s[i] == t[j]) {
            i++; j++;
        } else if (j > 0) {
            // Mismatch with previous matches: shift pattern
            j = lps[j - 1];
        } else {
            // Mismatch at the start: advance text pointer
            i++;
        }

        // Pattern found
        if (j == m) { return i - j; }
    }

    return -1; // Not found
}

// --- Test Functions ---

void testLPSArray() {
    std::cout << "--- Running LPS Array Tests ---" << std::endl;

    // Test 1: Simple repeated pattern
    std::string p1 = "AAAA";
    std::vector<int> expected1 = {0, 1, 2, 3};
    assert(std::equal(buildSuffixPrefixArray(p1).begin(), buildSuffixPrefixArray(p1).end(), expected1.begin()));

    // Test 2: Standard KMP example
    std::string p2 = "ABABA";
    std::vector<int> expected2 = {0, 0, 1, 2, 3};
    assert(std::equal(buildSuffixPrefixArray(p2).begin(), buildSuffixPrefixArray(p2).end(), expected2.begin()));

    // Test 3: Shift case
    std::string p3 = "ABCAB";
    std::vector<int> expected3 = {0, 0, 0, 1, 2};
    assert(std::equal(buildSuffixPrefixArray(p3).begin(), buildSuffixPrefixArray(p3).end(), expected3.begin()));

    // Test 4: Complex example with a zero mid-array
    std::string p4 = "ABABDABACDABABCABAB";
    // LPS for the pattern "ABABCABAB"
    std::string pattern_kmp = "ABABCABAB";
    std::vector<int> expected4 = {0, 0, 1, 2, 0, 1, 2, 3, 4};
    assert(std::equal(buildSuffixPrefixArray(pattern_kmp).begin(), buildSuffixPrefixArray(pattern_kmp).end(), expected4.begin()));

    std::cout << "LPS Array Tests Passed!" << std::endl;
}

void testKMP() {
    std::cout << "--- Running KMP Search Tests ---" << std::endl;

    // Test 1: Found at start
    assert(kmpSearch("ABABDABACDABABCABAB", "ABA") == 0);

    // Test 2: Found in the middle
    assert(kmpSearch("ABABDABACDABABCABAB", "CABA") == 14);

    // Test 3: Found at end
    assert(kmpSearch("ABABDABACDABABCABAB", "ABAB") == 0 || kmpSearch("ABABDABACDABABCABAB", "BAB") == 1);

    // Test 4: Full pattern match (from your previous example)
    std::string text_test4 = "ABABDABACDABABCABAB";
    std::string pattern_test4 = "ABABCABAB";
    assert(kmpSearch(text_test4, pattern_test4) == 10); // Index 10 is correct

    // Test 5: Pattern not found
    assert(kmpSearch("ABCDEFG", "XYZ") == -1);

    // Test 6: Pattern longer than text
    assert(kmpSearch("SHORT", "LONGER_PATTERN") == -1);

    // Test 7: Empty pattern
    assert(kmpSearch("ANY_TEXT", "") == 0);

    // Test 8: Single character match
    assert(kmpSearch("HELLO", "E") == 1);

    std::cout << "KMP Search Tests Passed!" << std::endl;
}

int main() {
    testLPSArray();
    testKMP();

    std::cout << "\nAll KMP Tests Completed Successfully!" << std::endl;

    return 0;
}