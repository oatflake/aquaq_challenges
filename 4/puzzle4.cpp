#include <iostream>
#include <string>
#include <numeric>
#include "../helper.h"

auto readInput() {
    int result;
    auto lambda = [&](auto line){
        result = std::stoi(line);
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    uint64_t sum = 0;
    for (int i = 1; i < input; i++) {
        if (std::gcd(input, i) == 1) {
            sum += i;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
