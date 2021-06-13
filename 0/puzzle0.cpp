#include <iostream>
#include <string>
#include <tuple>
#include "../helper.h"

std::vector<std::tuple<int, int>> readInput() {
    std::vector<std::tuple<int, int>> result;
    auto lambda = [&](const std::string& line){
        auto parts = split(line, " ");
        result.push_back({ std::stoi(parts[0]), std::stoi(parts[1]) });
    };
    readInputFile(lambda);
    return result;
}

int main() {
    std::array<std::string, 10> keys = { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    auto inputs = readInput();
    int count = 0;
    std::string result;
    for (auto [ key, presses ] : inputs) {
        result += keys[key][(presses - 1)];
    }
    std::cout << result << std::endl;
    return 0;
}
