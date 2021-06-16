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
    std::vector<int> numbers(input + 1);
    std::fill(numbers.begin(), numbers.end(), -1);
    numbers[0] = 0;
    for (int i = 1; i <= 20; i++) {
        numbers[i] = 1;
        numbers[i * 2] = 1;
        numbers[i * 3] = 1;
    }
    numbers[25] = 1;
    numbers[50] = 1;
    for (int i = 1; i <= input; i++) {
        if (numbers[i] != -1)
            continue;
        int min = numbers[i - 1] + 1;
        for (int j = 1; j <= i / 2; j++) {
            int darts = numbers[j] + numbers[i - j];
            if (darts < min)
                min = darts;
        }
        numbers[i] = min;
    }
    for (int i : numbers)
        result += i;
    std::cout << result << std::endl;
    return 0;
}
