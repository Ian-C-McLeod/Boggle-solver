#include "trie.hpp"

TrieNode::TrieNode() : isEndOfWord(false) {}

PrefixDictionary::PrefixDictionary() {
    root = std::make_unique<TrieNode>();
}



void PrefixDictionary::insert(const std::string& word) {
    TrieNode* node = root.get();
    for (char c : word) {
        if (!node->children.count(c)) {
            node->children[c] = std::make_unique<TrieNode>();
        }
        node = node->children[c].get();
    }
    node->isEndOfWord = true;
}

bool PrefixDictionary::isprefix(const std::string& prefix) {
    TrieNode* node = root.get();
    for (char c : prefix) {
        if (!node->children.count(c)) {
            return false;
        }
        node = node->children[c].get();
    }
    return true;
}

bool PrefixDictionary::isword(const std::string& word) {
    TrieNode* node = root.get();
    for (char c : word) {
        if (!node->children.count(c)) {
            return false;
        }
        node = node->children[c].get();
    }
    return node->isEndOfWord;
}

std::vector<std::string> PrefixDictionary::searchPrefix(const std::string& prefix) {
    TrieNode* node = root.get();
    for (char c : prefix) {
        if (!node->children.count(c)) {
            return {};
        }
        node = node->children[c].get();
    }

    std::vector<std::string> result;
    collectWords(node, prefix, result);
    return result;
}

void PrefixDictionary::collectWords(TrieNode* node, const std::string& prefix, std::vector<std::string>& result) {
    if (node->isEndOfWord) {
        result.push_back(prefix);
    }
    for (const auto& pair : node->children) {
        collectWords(pair.second.get(), prefix + pair.first, result);
    }
}
