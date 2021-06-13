#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::tuple<int, int, std::vector<std::tuple<int, int>>>> result;
    auto lambda = [&](const std::string& line){
        auto parts = split(line, " ");
        std::vector<std::tuple<int, int>> points;
        for (int i = 2; i < parts.size(); i += 2) {
            points.push_back({ std::stoi(parts[i]), std::stoi(parts[i + 1]) });
        }
        result.push_back({ std::stoi(parts[0]), std::stoi(parts[1]), points });
    };
    readInputFile(lambda);
    return result;
}

bool read(const std::vector<bool>& grid, int x, int y, int size) {
    if (x < 0 || x >= size || y < 0 || y >= size)
        return false;
    return grid[x + y * size];
}

int main() {
    int livingCells = 0;
    auto input = readInput();
    for (auto [steps, size, points] : input) {
        std::vector<bool> grid(size * size);
        std::fill(grid.begin(), grid.end(), false);
        for (auto [x, y] : points) {
            grid[x + y * size] = true;
        }
        std::vector<bool> gridCopy(size * size);
        for (int i = 0; i < steps; i++) {
            for (int y = 0; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    int neighbors = 0;
                    neighbors += read(grid, x - 1, y, size) ? 1 : 0;
                    neighbors += read(grid, x + 1, y, size) ? 1 : 0;
                    neighbors += read(grid, x, y - 1, size) ? 1 : 0;
                    neighbors += read(grid, x, y + 1, size) ? 1 : 0;
                    gridCopy[x + y * size] = neighbors % 2 == 1;
                }
            }
            grid.swap(gridCopy);
        }
        for (bool entry : grid) {
            livingCells += entry ? 1 : 0;
        }
    }
    std::cout << livingCells << std::endl;
    return 0;
}
