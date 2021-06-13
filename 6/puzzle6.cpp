#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    int result;
    auto lambda = [&](auto line){
        result = std::stoi(split(line, " ")[5]);
    };
    readInputFile(lambda);
    return result;
}

int ones(int x) {
    int result = 0;
    while (x > 0) {
        result += x % 10 == 1 ? 1 : 0;
        x /= 10;
    }
    return result;
}

int main() {
    int result = 0;
    int number = readInput();
    for (int i = 0; i <= number; i++) {
        for (int j = 0; i + j <= number; j++) {
            int k = number - i - j;
            if (i + j + k == number) {
                result += ones(i) + ones(j) + ones(k);
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}
