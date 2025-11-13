#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class WordLadderII {
private:
    /**
     * Helper function to find all 1-edit distance neighbors that are in the remaining word set.
     */
    vector<string> get_neighbors(const string& current_word, const unordered_set<string>& word_set) {
        vector<string> neighbors;
        string temp_word = current_word;

        for (size_t i = 0; i < temp_word.length(); ++i) {
            char original_char = temp_word[i];

            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == original_char) continue;

                temp_word[i] = c;

                // Use .count() for checking existence (equivalent to Kotlin's 'in')
                if (word_set.count(temp_word)) {
                    neighbors.push_back(temp_word);
                }
            }
            temp_word[i] = original_char; // Backtrack to original character
        }
        return neighbors;
    }

    /**
     * Phase 2: DFS (Backtracking) to reconstruct all paths
     */
    void dfs_reconstruct(
        const string& current_word,
        const string& begin_word,
        const unordered_map<string, vector<string>>& predecessor_map,
        vector<string>& current_path,
        vector<vector<string>>& all_shortest_paths
    ) {
        // Add current word to the path (path is being built backwards)
        current_path.push_back(current_word);

        if (current_word == begin_word) {
            // Found a full path. Reverse it for the correct order (begin -> end) and add
            vector<string> path = current_path;
            ranges::reverse(path);
            all_shortest_paths.push_back(path);
        } else {
            // Get all predecessors that lead to 'current_word' on a shortest path
            if (predecessor_map.contains(current_word)) {
                for (const string& predecessor : predecessor_map.at(current_word)) {
                    dfs_reconstruct(predecessor, begin_word, predecessor_map, current_path, all_shortest_paths);
                }
            }
        }

        // Backtrack: Remove the current word before returning
        current_path.pop_back();
    }


public:
    vector<vector<string>> findLadders(
        const string& begin_word,
        const string& end_word,
        const vector<string>& word_list
    ) {
        // Use an unordered_set for O(1) lookups and level management
        unordered_set<string> word_set(word_list.begin(), word_list.end());

        // Check if end_word exists
        if (!word_set.contains(end_word)) return {};

        // Remove begin_word if it's in the list
        word_set.erase(begin_word);

        // --- Phase 1: BFS to find the shortest distance and build the predecessor map ---

        // Map: word -> list of words that lead to it (predecessors)
        unordered_map<string, vector<string>> predecessor_map;

        // Set holds all words at the current level
        unordered_set<string> current_level({begin_word});

        bool found_shortest_path = false;

        while (!current_level.empty() && !found_shortest_path) {
            unordered_set<string> next_level;

            // Critical Step: Remove words in the current level from the word_set.
            // This ensures only unvisited words (at the next distance) are considered, guaranteeing shortest paths.
            for (const string& word : current_level) {
                word_set.erase(word);
            }

            for (const string& current_word : current_level) {
                // Generate all 1-edit distance neighbors
                for (const string& next_word : get_neighbors(current_word, word_set)) {

                    if (next_word == end_word) {
                        found_shortest_path = true;
                    }

                    // Build predecessor map: next_word is reachable from current_word
                    predecessor_map[next_word].push_back(current_word);

                    next_level.insert(next_word);
                }
            }
            current_level = next_level;
        }

        // --- Phase 2: DFS to reconstruct all shortest paths using the predecessor map ---

        if (!found_shortest_path) return {};

        vector<vector<string>> all_shortest_paths;
        vector<string> current_path;

        // Start DFS from the end_word, traversing back to the begin_word
        dfs_reconstruct(end_word, begin_word, predecessor_map, current_path, all_shortest_paths);

        return all_shortest_paths;
    }
};
