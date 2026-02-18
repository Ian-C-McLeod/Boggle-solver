#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class TrieNode {
public:
    bool isEndOfWord;
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;

    TrieNode();
};

class PrefixDictionary {
private:
    std::unique_ptr<TrieNode> root;

    void collectWords(TrieNode* node, const std::string& prefix, std::vector<std::string>& result);

public:
    PrefixDictionary();

    void insert(const std::string& word);
    bool isprefix(const std::string& prefix);
    bool isword(const std::string& word);
    std::vector<std::string> searchPrefix(const std::string& prefix);
};
#endif // TRIE_HPP