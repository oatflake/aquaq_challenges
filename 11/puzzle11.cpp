#include <iostream>
#include <string>
#include <math.h>
#include "../helper.h"

auto readInput() {
    int i = -1;
    std::vector<std::tuple<int, int, int, int>> result;
    auto lambda = [&](const std::string& line){
        if (i >= 0) {
            auto s = split(line, ",");
            result.push_back({ std::stoi(s[0]), std::stoi(s[1]), std::stoi(s[2]), std::stoi(s[3]) });
        }
        i++;
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    int minX = INT32_MAX, minY = INT32_MAX;
    int maxX = INT32_MIN, maxY = INT32_MIN;
    for (auto [lx,ly,ux,uy] : input) {
        minX = std::min(lx, minX);
        minY = std::min(ly, minY);
        maxX = std::max(ux, maxX);
        maxY = std::max(uy, maxY);
    }
    // weird input, upper right corner is actually outside of the rectangle...
    int width = maxX - minX;
    int height = maxY - minY;
    std::vector<int> grid(width * height);
    std::fill(grid.begin(), grid.end(), 0);
    for (auto [lx,ly,ux,uy] : input) {
        for (int y = ly - minY; y < uy - minY; y++) {
            for (int x = lx - minX; x < ux - minX; x++) {
                grid[x + y * width] += 1;
            }
        }
    }
    for (auto [lx,ly,ux,uy] : input) {
        bool keep = false;
        for (int y = ly - minY; y < uy - minY; y++) {
            for (int x = lx - minX; x < ux - minX; x++) {
                if (grid[x + y * width] > 1)
                    keep = true;
            }
        }
        if (!keep) {
            for (int y = ly - minY; y < uy - minY; y++) {
                for (int x = lx - minX; x < ux - minX; x++) {
                    grid[x + y * width] = 0;
                }
            }
        }
    }
    int result = 0;
    for (int tile : grid) {
        result += tile > 0 ? 1 : 0;
    }
    std::cout << result << std::endl;
    return 0;
}
