#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <memory>

using std::vector;
using std::string;
using std::map;
using std::unique_ptr;
using std::make_unique;

struct TrieNode {
    char ch = '*';
    bool isWord = false;
    map<char, unique_ptr<TrieNode>> children;

    TrieNode(char c = '*') : ch(c) {}
};

class Trie {
public:
    unique_ptr<TrieNode> root;

    Trie() : root(make_unique<TrieNode>()) {}

    void insert(const string& word) {
        TrieNode* currentNode = root.get();

        for (char ch : word) {
            // Clean try_emplace like Kotlin's getOrPut
            auto [it, _] = currentNode->children.try_emplace(ch, make_unique<TrieNode>(ch));
            currentNode = it->second.get();
        }

        currentNode->isWord = true;
    }

    vector<string> search(const string& prefix) const {
        vector<string> results;
        const TrieNode* currentNode = root.get();

        // Navigate to prefix node
        for (char ch : prefix) {
            auto it = currentNode->children.find(ch);
            if (it == currentNode->children.end()) return results;
            currentNode = it->second.get();
        }

        // Collect and sort words
        collectWords(currentNode, prefix, results);
        std::sort(results.begin(), results.end());
        if (results.size() > 3) results.resize(3);

        return results;
    }

private:
    void collectWords(const TrieNode* node, string currentPrefix, vector<string>& results) const {
        if (node->isWord) results.push_back(currentPrefix);

        for (auto const& [ch, childPtr] : node->children) {
            collectWords(childPtr.get(), currentPrefix + ch, results);
        }
    }
};

class SearchSuggestionSystem {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, const string& searchWord) {
        Trie trie;
        vector<vector<string>> result;

        for (const auto& product : products) {
            trie.insert(product);
        }

        string prefix;
        for (const char ch : searchWord) {
            prefix += ch;
            result.emplace_back(trie.search(prefix));
        }

        return result;
    }
};
