#include <iostream>
#include <string>
#include <unordered_map>
#include "../helper.h"

auto readInput() {
    std::vector<std::vector<int>> result;
    auto lambda = [&](const std::string& line){
        std::vector<int> numbers;
        auto parts = split(line, " ");
        for (const auto& part : parts) {
            numbers.push_back(std::stoi(part));
        }
        result.push_back(numbers);
    };
    readInputFile(lambda);
    return result;
}

const std::array<int, 25> grid = { 
    6,  17, 34, 50, 68,
    10, 21, 45, 53, 66,
    5,  25, 36, 52, 69,
    14, 30, 33, 54, 63,
    15, 23, 41, 51, 62
};

bool bingo(const std::array<bool, 25>& marked) {
    // check rows
    for (int y = 0; y < 5; y++) {
        bool won = true;
        for (int x = 0; x < 5; x++) {
            won &= marked[x + y * 5];
        }
        if (won)
            return true;
    }
    // check columns
    for (int x = 0; x < 5; x++) {
        bool won = true;
        for (int y = 0; y < 5; y++) {
            won &= marked[x + y * 5];
        }
        if (won)
            return true;
    }
    { // check diagonal
        bool won = true;
        for (int i = 0; i < 5; i++) {
            won &= marked[i + i * 5];
        }
        if (won)
            return true;
    }
    { // check other diagonal
        bool won = true;
        for (int i = 0; i < 5; i++) {
            won &= marked[4 - i + i * 5];
        }
        if (won)
            return true;
    }
    return false;
}

int main() {
    auto input = readInput();
    int result = 0;
    std::unordered_map<int, int> numberToCell;
    for (int i = 0; i < grid.size(); i++) {
        numberToCell[grid[i]] = i;
    }
    for (auto sequence : input) {
        std::array<bool, 25> marked;
        marked.fill(false);
        int i;
        for (i = 0; i < sequence.size(); i++) {
            int number = sequence[i];
            auto iter = numberToCell.find(number);
            if (iter != numberToCell.end()) {
                marked[iter->second] = true;
                if (bingo(marked)) {
                    i += 1;
                    break;
                }
            }
        }
        result += i;
    }
    std::cout << result << std::endl;
    return 0;
}
