#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::tuple<int, int>> shopping;
    int i = -1;
    auto lambda = [&](auto line){
        if (i >= 0) {
            auto parts = split(line, ",");
            shopping.push_back({ std::stoi(parts[1]), std::stoi(parts[2]) });
        }
        i++;
    };
    readInputFile(lambda);
    return shopping;
}

int main() {
    std::array<int, 5> milk = { 0, 0, 0, 0, 0 };
    int cereal = 0;
    auto shopping = readInput();
    int day = 0;
    for (auto [newMilk, newCereal] : shopping) {
        cereal += newCereal;
        int i = 0;
        for (; i < 5; i++) {
            if (milk[(day + i) % 5] >= 100 && cereal >= 100) {
                milk[(day + i) % 5] -= 100;
                cereal -= 100;
                break;
            }
        }
        milk[day % 5] = newMilk;
        day++;
    }
    int leftOver = cereal;
    for (int m : milk) {
        leftOver += m;
    }
    std::cout << leftOver << std::endl;
    return 0;
}
