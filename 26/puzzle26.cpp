#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::vector<u_int8_t>> result;
    auto lambda = [&](const std::string& line){
        std::vector<u_int8_t> digits;
        for (char c : line) {
            digits.push_back(c - '0');
        }
        result.push_back(digits);
    };
    readInputFile(lambda);
    return result;
}

int toNumber(std::vector<u_int8_t> number, int from) {
    int result = 0;
    int d = 1;
    for (int i = number.size() - 1; i >= from; i--) {
        result += d * number[i];
        d *= 10;
    }
    return result;
}

int main() {
    int result = 0;
    auto input = readInput();
    for (auto& number : input) {
        int max = number.back();
        for (int i = number.size() - 2; i >= 0; i--) {
            int digit = number[i];
            if (digit > max) {
                max = digit;
            }
            if (digit < max) {  // postfix can be turned into larger number
                int previous = toNumber(number, i);
                // construct new number
                int swapIndex = -1;
                for (int j = i + 1; j < number.size(); j++) {
                    if (number[j] > number[i] && (swapIndex == -1 || number[swapIndex] > number[j]))
                        swapIndex = j;
                }
                int tmp = number[swapIndex];
                number[swapIndex] = number[i];
                number[i] = tmp;
                std::sort(number.begin() + i + 1, number.end());
                // only the modified postfix matters when computing the difference
                int now = toNumber(number, i);
                result += now - previous;
                break;
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}
