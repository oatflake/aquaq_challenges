#include <iostream>
#include <string>
#include <tuple>
#include "../helper.h"

std::string room = "\
  ##  \
 #### \
######\
######\
 #### \
  ##  \
";

bool valid(int x, int y) {
    if (x < 0 || x > 5 || y < 0 || y > 5)
        return false;
    return room[x + y * 6] == '#';
}

auto readInput() {
    std::vector<std::tuple<int, int>> result;
    auto lambda = [&](auto line){
        for (char c : line) {
            if (c == 'L')
                result.push_back({ -1, 0 });
            if (c == 'R')
                result.push_back({ 1, 0 });
            if (c == 'U')
                result.push_back({ 0, -1 });
            if (c == 'D')
                result.push_back({ 0, 1 });
        }
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    int x = 2, y = 0;
    int sum = 0;
    for (auto [dx, dy] : input) {
        if (valid(x + dx, y + dy)) {
            x += dx;
            y += dy;
        }
        sum += x + y;
    }
    std::cout << sum << std::endl;
    return 0;
}
