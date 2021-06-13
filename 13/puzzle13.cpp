#include <iostream>
#include <string>
#include <math.h>
#include "../helper.h"

auto readInput() {
    std::vector<std::string> result;
    auto lambda = [&](const std::string& line){
        result.push_back(line);
    };
    readInputFile(lambda);
    return result;
}

int repeatingPrefix(std::string line) {
    for (int len = 1; len <= line.length() / 2; len++) {
        if (line.substr(0, len) == line.substr(len, len)) {
            std::string pattern = line.substr(0, len);
            int result = 0;
            int i = 0;
            while (line.substr(i, len) == pattern) {
                result++;
                i += len;
            }
            return result;
        }
    }
    return -1;
}

int main() {
    auto input = readInput();
    int result = 0;
    for (auto& line : input) {
        int repeatedPrefix = repeatingPrefix(line);
        if (repeatedPrefix == -1) {
            std::reverse(line.begin(), line.end());
            repeatedPrefix = repeatingPrefix(line);
        }
        result += repeatedPrefix;
    }
    std::cout << result << std::endl;
    return 0;
}
