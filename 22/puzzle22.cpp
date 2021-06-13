#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<int> result;
    auto lambda = [&](const std::string& line){
        auto parts = split(line, " ");
        for (const auto& part : parts) {
            result.push_back(std::stoi(part));
        }
    };
    readInputFile(lambda);
    return result;
}

std::string numToRoman(int n) {
    std::array<std::tuple<int, std::string>, 13> table = {
        std::make_tuple(1000, "M"), { 900, "CM" }, { 500, "D" }, { 400, "CD" }, { 100, "C" }, 
        { 90, "XC" }, { 50, "L" }, { 40, "XL" }, { 10, "X" }, { 9, "IX" },
        { 5, "V" }, { 4, "IV" }, { 1, "I" }
    };
    std::string result;
    while (n > 0) {
        for (auto [ value, letters ] : table) {
            if (n >= value) {
                result += letters;
                n -= value;
                break;
            }
        }
    }
    return result;
}

int caesarChiffre(const std::string& word) {
    int num = 0;
    for (int i = word.length() - 1; i >= 0; i--) {
        num += word[i] - 'A' + 1;
    }
    return num;
}

int main() {
    auto input = readInput();
    int result = 0;
    for (auto num : input) {
        result += caesarChiffre(numToRoman(num));
    }
    std::cout << result << std::endl;
    return 0;
}
