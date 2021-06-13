#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::string result;
    auto lambda = [&](const std::string& line){
        result = line;
    };
    readInputFile(lambda);
    return result;
}

std::string getKey(const std::string& password) {
    std::array<bool, 25> usedLetters;
    usedLetters.fill(false);
    std::string key;
    for (char c : password) {
        if (c == ' ')
            continue;
        int i = c - 'a' - (c > 'j' ? 1 : 0);
        if (usedLetters[i])
            continue;
        usedLetters[i] = true;
        key += c;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j')
            continue;
        int i = c - 'a' - (c > 'j' ? 1 : 0);
        if (usedLetters[i])
            continue;
        usedLetters[i] = true;
        key += c;
    }
    return key;
}

std::string decrypt(const std::string& key, const std::string& cypherText) {
    std::unordered_map<char, int> toIndex;
    for (int i = 0; i < key.length(); i++) {
        toIndex[key[i]] = i;
    }
    std::string clearText;
    for (int i = 0; i < cypherText.length(); i += 2) {
        int a = toIndex[cypherText[i]];
        int b = toIndex[cypherText[i + 1]];
        if (a / 5 == b / 5) {
            int ax = a % 5;
            int ay = a / 5;
            int bx = b % 5;
            int by = b / 5;
            ax = (ax - 1 + 5) % 5;
            bx = (bx - 1 + 5) % 5;
            clearText += key[ax + ay * 5];
            clearText += key[bx + by * 5];
        } else if (a % 5 == b % 5) {
            int ax = a % 5;
            int ay = a / 5;
            int bx = b % 5;
            int by = b / 5;
            ay = (ay - 1 + 5) % 5;
            by = (by - 1 + 5) % 5;
            clearText += key[ax + ay * 5];
            clearText += key[bx + by * 5];
        } else {
            int ax = a % 5;
            int ay = a / 5;
            int bx = b % 5;
            int by = b / 5;
            clearText += key[bx + ay * 5];
            clearText += key[ax + by * 5];
        }
    }
    //clearText.erase(remove(clearText.begin(), clearText.end(), 'x'), clearText.end());    // answer has to contain padding
    return clearText;
}

int main() {
    auto input = readInput();
    std::cout << decrypt(getKey("power plant"), input) << std::endl;
    return 0;
}
