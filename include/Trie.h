#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

struct TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    std::vector<int> contactIds; // Can hold multiple IDs for duplicate names
    bool isEndOfWord = false;
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;

    void dfsSearch(TrieNode* node, std::vector<int>& results) const {
        if (!node) return;
        if (node->isEndOfWord) {
            for (int id : node->contactIds) {
                // Avoid duplicates in results
                if (std::find(results.begin(), results.end(), id) == results.end()) {
                    results.push_back(id);
                }
            }
        }
        for (const auto& pair : node->children) {
            dfsSearch(pair.second.get(), results);
        }
    }

public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& name, int id) {
        TrieNode* current = root.get();
        for (char ch : name) {
            char lowerCh = std::tolower(ch);
            if (current->children.find(lowerCh) == current->children.end()) {
                current->children[lowerCh] = std::make_unique<TrieNode>();
            }
            current = current->children[lowerCh].get();
        }
        current->isEndOfWord = true;
        current->contactIds.push_back(id);
    }

    std::vector<int> searchPrefix(const std::string& prefix) const {
        std::vector<int> results;
        TrieNode* current = root.get();
        for (char ch : prefix) {
            char lowerCh = std::tolower(ch);
            if (current->children.find(lowerCh) == current->children.end()) {
                return results; // Prefix not found
            }
            current = current->children[lowerCh].get();
        }
        // Run DFS from the end of the prefix to gather all matches
        dfsSearch(current, results);
        return results;
    }
};