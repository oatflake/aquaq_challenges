#include <iostream>
#include <string>
#include <math.h>
#include "../helper.h"

auto readInput() {
    std::vector<std::tuple<int, int>> result;
    auto lambda = [&](const std::string& line){
        auto s = split(line, " ");
        result.push_back({ std::stoi(s[0]), std::stoi(s[1]) });
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto floors = readInput();
    int result = 1;
    int currentFloor = 0;
    bool moveUp = true;
    while (currentFloor >= 0 && currentFloor < floors.size()) {
        auto [direction, amount] = floors[currentFloor];
        if (direction == 0)
            moveUp = !moveUp;
        currentFloor += moveUp ? amount : -amount;
        result++;
    }
    std::cout << result << std::endl;
    return 0;
}
