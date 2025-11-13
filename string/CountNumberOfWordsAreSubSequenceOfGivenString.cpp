#include <vector>
#include <string>
#include <queue>
using namespace std;

struct WordState {
    int wordIndex;
    int charIndex;
    
    WordState(int w, int c) : wordIndex(w), charIndex(c) {}
};

class Solution {
public:
    int numMatchingSubseq(const string& s, const vector<string>& words) {
        // Create queues for each character (a-z)
        vector<queue<WordState>> waiting(26);
        
        // Initialize: add each word to the queue of its first character
        for (int i = 0; i < words.size(); i++) {
            if (!words[i].empty()) {
                char firstChar = words[i][0];
                waiting[firstChar - 'a'].emplace(i, 0);
            }
        }
        
        int count = 0;
        
        // Process each character in the main string
        for (const char &c : s) {
            auto& q = waiting[c - 'a'];
            const int currentSize = q.size();
            
            // Process all words waiting for current character
            for (int i = 0; i < currentSize; i++) {
                WordState current = q.front();
                q.pop();
                
                // Move to next character in this word
                current.charIndex++;
                
                // Check if we've reached the end of the word
                if (current.charIndex == words[current.wordIndex].size()) {
                    count++;
                } else {
                    // Get next character and add to corresponding queue
                    char nextChar = words[current.wordIndex][current.charIndex];
                    waiting[nextChar - 'a'].push(current);
                }
            }
        }
        
        return count;
    }
};
