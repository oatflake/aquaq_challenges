#include <iostream>
#include <string>
#include <algorithm>
#include "../helper.h"

auto readInput() {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    auto lambda = [&](std::string line){
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        if (line.length() == 0) {
            result.push_back(current);
            current = {};
        } else {
            auto parts = split(line, ":");
            int h = std::stoi(parts[0]);
            int m = std::stoi(parts[1]);
            parts = split(parts[2], ".");
            int s = std::stoi(parts[0]);
            int ms = std::stoi(parts[1]);
            current.push_back(h * 60 * 60 * 1000 + m * 60 * 1000 + s * 1000 + ms);
        }
    };
    readInputFile(lambda);
    return result;
}

std::array<std::string, 26> morseCode = {
    ".-",   "-...", "-.-.", "-..",  ".",
    "..-.", "--.",  "....", "..",   ".---",
    "-.-",  ".-..", "--",   "-.",   "---",
    ".--.", "--.-", ".-.",  "...",  "-",
    "..-",  "...-", ".--",  "-..-", "-.--",
    "--.."
};

int main() {
    auto input = readInput();
    std::unordered_map<std::string, char> morseToLetters;
    for (int i = 0; i < morseCode.size(); i++) {
        morseToLetters[morseCode[i]] = 'a' + i;
    }
    std::string result;
    for (const auto& clicks : input) {
        std::string code;
        for (int i = 0; i < clicks.size(); i += 2) {
            int clickLength = clicks[i + 1] - clicks[i];
            code += clickLength < 1500 ? "." : "-";
            if (i + 2 >= clicks.size() || clicks[i + 2] - clicks[i + 1] > 1500) {
                result += morseToLetters[code];
                code = "";
            }
        }
        result += " ";
    }
    std::cout << result << std::endl;
    return 0;
}
