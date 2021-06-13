#include <iostream>
#include <string>
#include <math.h>
#include "../helper.h"

auto readInput() {
    std::string result;
    auto lambda = [&](auto line){
        result = line;
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        input[i] = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ? input[i] : '0';
    }
    int step = (int) std::ceil(input.length() / 3.0f);
    for (int i = 0; i < input.length(); i += step) {
        std::cout << input[i] << input[i + 1];
    }
    std::cout << std::endl;
    return 0;
}
