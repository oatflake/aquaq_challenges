#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<int> result;
    auto lambda = [&](const std::string& line){
        auto parts = split(line, ":");
        result.push_back(60 * 60 * std::stoi(parts[0]) + 60 * std::stoi(parts[1]) + std::stoi(parts[2]));
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    std::vector<int> palindromTimes;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 5; j++) {
            for (int k = 0; k <= 5; k++) {
                if (i * 10 + j > 23)
                    continue;
                palindromTimes.push_back(60 * 60 * (i * 10 + j) + 60 * (k * 10 + k) + (j * 10 + i));
            }
        }
    }
    int N = 24 * 60 * 60;
    int result = 0;
    for (int i : input) {
        int minDistance = INT32_MAX;
        for (int p : palindromTimes) {
            int max = std::max(i, p);
            int min = std::min(i, p);
            int distance = std::min(max - min, N - max + min);
            minDistance = std::min(minDistance, distance);
        }
        result += minDistance;
    }
    std::cout << result << std::endl;
    return 0;
}
