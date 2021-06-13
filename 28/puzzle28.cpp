#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::string result;
    int width;
    int height = 0;
    auto lambda = [&](const std::string& line) {
        result += line;
        width = line.length();
        height++;
    };
    readInputFile(lambda);
    return std::make_tuple(result, width, height);
}

int main() {
    auto [grid, width, height] = readInput();
    std::string word = "FISSION_MAILED";
    std::string encrypted;
    for (char c : word) {
        int y = 0;
        for (; y < height; y++) {
            if (c == grid[y * width])
                break;
        }
        int x = 0;
        int dirX = 1;
        int dirY = 0;
        char newChar;
        do {
            x += dirX;
            y += dirY;
            newChar = grid[x + y * width];
            if (newChar == '/') {
                int tmp = dirX;
                dirX = -dirY;
                dirY = -tmp;
                grid[x + y * width] = '\\';
            }
            if (newChar == '\\') {
                int tmp = dirX;
                dirX = dirY;
                dirY = tmp;
                grid[x + y * width] = '/';
            }
        } while (newChar == ' ' || newChar == '/' || newChar == '\\');
        encrypted += newChar;
    }
    std::cout << encrypted << std::endl;
    return 0;
}
