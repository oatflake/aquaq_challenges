#include <iostream>
#include <string>
#include <unordered_map>
#include "../helper.h"

auto readInput() {
    std::vector<int> result;
    auto lambda = [&](auto line){
        auto parts = split(line, " ");
        for (const auto& part : parts) {
            result.push_back(std::stoi(part));
        }
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    std::vector<int> filtered;
    std::unordered_map<int, int> seen;
    for (int i = 0; i < input.size(); i++) {
        auto iter = seen.find(input[i]);
        if (iter != seen.end()) {
            for (int j = filtered.size() - 1; j > iter->second; j--) {
                seen.erase(filtered.back());
                filtered.pop_back();
            }
        } else {
            filtered.push_back(input[i]);
            seen[input[i]] = filtered.size() - 1;
        }
    }
    int result = 0;
    for (int v : filtered)
        result += v;
    std::cout << result << std::endl;
    return 0;
}
