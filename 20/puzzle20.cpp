#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::vector<int>> result;
    auto lambda = [&](const std::string& line){
        auto parts = split(line, " ");
        std::vector<int> cards;
        for (const auto& part : parts) {
            if (part == "J" || part == "Q" || part == "K")
                cards.push_back(10);
            else if (part == "A")
                cards.push_back(1);
            else
                cards.push_back(std::stoi(part));
        }
        result.push_back(cards);
    };
    readInputFile(lambda);
    return result;
}

int main() {
    int wins = 0;
    auto input = readInput();
    for (const auto& cards : input) {
        int score = 0;
        bool haveAce = false;
        for (int card : cards) {
            if (card == 1)
                haveAce = true;
            score += card;
            if (score == 21 || (haveAce && score == 11)) {
                score = 0;
                haveAce = false;
                wins++;
            }
            if (score > 21) {
                score = 0;
                haveAce = false;
            }
        }
    }
    std::cout << wins << std::endl;
    return 0;
}
