#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    int result;
    auto lambda = [&](const std::string& line) {
        result = std::stoi(line);
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    int result = 0;
    for (int i = 0; i <= input; i++) {
        int num = i;
        int digit = num % 10;
        bool ok = true;
        while (num > 0) {
            int digit2 = num % 10;
            if (digit2 > digit) {
                ok = false;
                break;
            }
            digit = digit2;
            num /= 10;
        }
        if (ok) {
            result++;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
