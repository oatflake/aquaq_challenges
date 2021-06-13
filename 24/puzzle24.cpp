#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include "../helper.h"

auto readInput() {
    std::vector<std::string> result;
    auto lambda = [&](const std::string& line){
        result.push_back(line);
    };
    readInputFile(lambda);
    return result;
}

struct Tree {
    std::string content;
    int weight;
    std::shared_ptr<Tree> left;
    std::shared_ptr<Tree> right;
    Tree(std::string c, int weight) : 
        content(c), weight(weight) {}
    Tree(std::string c, int weight, std::shared_ptr<Tree> left, std::shared_ptr<Tree> right) : 
        content(c), weight(weight), left(left), right(right) {}
};

int main() {
    auto input = readInput();
    // count char frequencies
    std::unordered_map<char, int> chars;
    for (char c : input[0]) {
        if (chars.find(c) == chars.end())
            chars[c] = 0;
        chars[c]++;
    }
    // create tree
    auto comp = [](std::shared_ptr<Tree> a, std::shared_ptr<Tree> b){ 
        if (a->weight != b->weight)
            return a->weight > b->weight;
        if (a->content.length() != b->content.length())
            return a->content.length() > b->content.length();
        return a->content[0] > b->content[0];
    };
    std::priority_queue<std::shared_ptr<Tree>, std::vector<std::shared_ptr<Tree>>, decltype(comp)> queue(comp);
    for (auto entry : chars) {
        std::string s;
        s += entry.first;
        queue.push(std::make_shared<Tree>(s, entry.second));        
    }
    while (queue.size() > 1) {
        auto first = queue.top();
        queue.pop();
        auto second = queue.top();
        queue.pop();
        queue.push(std::make_shared<Tree>(first->content + second->content, first->weight + second->weight, first, second));
    }
    auto root = queue.top();
    // parse huffman code
    std::string result;
    auto current = root;
    for (int i = 0; i < input[1].length(); i++) {
        if (input[1][i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->content.length() == 1) {
            result += current->content;
            current = root;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
