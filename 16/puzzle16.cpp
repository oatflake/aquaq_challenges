#include <iostream>
#include <string>
#include <math.h>
#include "../helper.h"

struct Letter {
    std::array<int, 6> rightMostRowEntry;   // count from left
    std::array<int, 6> leftMostRowEntry;    // count from right
    uint32_t totalLetterWidth = 0;
    uint32_t usedTiles = 0;
};

auto readAlphabet() {
    std::vector<Letter> result;
    int i = 0;
    auto lambda = [&](const std::string& line){
        if (i % 6 == 0) {
            result.push_back(Letter());
        }
        Letter* letter = &result[result.size() - 1];
        letter->totalLetterWidth = std::max(letter->totalLetterWidth, (uint32_t) line.length());
        for (char c : line) {
            if (c == '#')
                letter->usedTiles++;
        }
        letter->rightMostRowEntry[i % 6] = line.find_last_of('#') + 1;
        letter->leftMostRowEntry[i % 6] = line.find_first_of('#');
        if (i % 6 == 5) {
            for (int j = 0; j < 6; j++) {
                letter->leftMostRowEntry[j] = letter->totalLetterWidth - letter->leftMostRowEntry[j];
            }
        }
        i++;
    };
    readInputFile(lambda, "asciialphabet.txt");
    return result;
}

auto readInput() {
    std::vector<int> result;
    auto lambda = [&](const std::string& line){
        for (char c : line) {
            result.push_back(c - 'A');
        }
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto letters = readAlphabet();
    auto input = readInput();
    int emptySpaces = letters[input[0]].totalLetterWidth * 6 - letters[input[0]].usedTiles;
    for (int k = 1; k < input.size(); k++) {
        int kerning = 0;
        int i = input[k];
        for (int j = 0; j < 6; j++) {
            kerning = std::max(kerning, letters[i].leftMostRowEntry[j] + letters[input[k - 1]].rightMostRowEntry[j]);
        }
        int kerningChars = letters[i].totalLetterWidth + letters[input[k - 1]].totalLetterWidth - 1 - kerning;
        emptySpaces += letters[i].totalLetterWidth * 6 - letters[i].usedTiles - kerningChars * 6;
    }
    std::cout << emptySpaces << std::endl;
    return 0;
}
