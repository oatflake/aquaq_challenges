#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::string> result;
    auto lambda = [&](const std::string& line) {
        result.push_back(line);
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    int result = 0;
    for (const auto& word : input) {
        int moves = std::count(word.begin(), word.end(), '1');
        result += moves % 2 == 1 ? moves / 2 + 1 : 0;
    }
    std::cout << result << std::endl;
    return 0;
}
