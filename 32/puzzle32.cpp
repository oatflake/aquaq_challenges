#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::string> result;
    auto lambda = [&](const std::string& line) {
        result.push_back(line);
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    int result = 0;
    std::vector<char> stack;
    for (const auto& line : input) {
        stack.clear();
        bool wrongClosingBracket = false;
        for (char c : line) {
            if (c == '(' || c == '[' || c == '{')
                stack.push_back(c);
            if (c == ')') {
                if (stack.size() > 0 && stack.back() == '(') {
                    stack.pop_back();
                } else {
                    wrongClosingBracket = true;
                    break;
                }
            }
            if (c == ']') {
                if (stack.size() > 0 && stack.back() == '[') {
                    stack.pop_back();
                } else {
                    wrongClosingBracket = true;
                    break;
                }
            }
            if (c == '}') {
                if (stack.size() > 0 && stack.back() == '{') {
                    stack.pop_back();
                } else {
                    wrongClosingBracket = true;
                    break;
                }
            }
        }
        if (!wrongClosingBracket && stack.size() == 0)
            result++;
    }
    std::cout << result << std::endl;
    return 0;
}
