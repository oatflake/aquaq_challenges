#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "../helper.h"

auto readWords() {
    std::vector<std::string> result;
    auto lambda = [&](const std::string& line){
        result.push_back(line.substr(0, line.length() - 1));
    };
    readInputFile(lambda, "words.txt");
    return result;
}

auto readInput() {
    std::vector<std::tuple<std::string, std::string>> result;
    auto lambda = [&](const std::string& line){
        auto words = split(line, ",");
        result.push_back({ words[0], words[1] });
    };
    readInputFile(lambda);
    return result;
}

std::vector<int> bfs(const std::vector<std::vector<int>>& nodes, int start, int goal) {
    std::queue<std::tuple<int, int>> queue;
    std::unordered_map<int, int> seen;
    queue.push({ start, -1 });
    seen[start] = -1;
    bool foundPath = false;
    while (!queue.empty()) {
        auto [current, parent] = queue.front();
        queue.pop();
        if (current == goal) {
            foundPath = true;
            break;
        }
        for (int child : nodes[current]) {
            if (seen.find(child) == seen.end()) {
                queue.push({ child, current });
                seen[child] = current;
            }
        }
    }
    if (!foundPath)
        return {};
    std::vector<int> path;
    int current = goal;
    while (current != -1) {
        path.push_back(current);
        current = seen[current];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    auto words = readWords();
    auto input = readInput();
    int minWordSize = INT32_MAX;
    int maxWordSize = INT32_MIN;
    for (auto [from, to] : input) {
        minWordSize = std::min(minWordSize, (int) std::min(from.length(), to.length()));
        maxWordSize = std::max(minWordSize, (int) std::max(from.length(), to.length()));
    }
    // create nodes
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b){ return a.length() < b.length(); });
    std::unordered_map<std::string, int> stringToNode;
    std::vector<std::vector<int>> nodes;
    int firstUsedWord = -1;
    int lastUsedWord = -1;
    for (int i = 0; i < words.size(); i++) {
        if (words[i].length() < minWordSize)    // could use binary search instead...
            continue;
        if (words[i].length() > maxWordSize)    // could use binary search instead...
            break;
        if (firstUsedWord == -1)
            firstUsedWord = i;
        lastUsedWord = i;
        stringToNode[words[i]] = i - firstUsedWord;
        nodes.push_back({});
    }
    // create edges
    for (int i = firstUsedWord; i <= lastUsedWord; i++) {
        for (int j = i + 1; j < words.size(); j++) {
            if (words[i].length() != words[j].length())
                break;
            int differences = 0;
            for (int l = 0; l < words[i].length(); l++) {
                if (words[i][l] != words[j][l])
                    differences++;
            }
            if (differences == 1) {
                nodes[i - firstUsedWord].push_back(j - firstUsedWord);
                nodes[j - firstUsedWord].push_back(i - firstUsedWord);
            }
        }
    }
    // calculate product of paths' lengths
    int result = 1;
    for (auto [from, to] : input) {
        auto path = bfs(nodes, stringToNode[from], stringToNode[to] );
        result *= path.size();
    }
    std::cout << result << std::endl;
    return 0;
}
