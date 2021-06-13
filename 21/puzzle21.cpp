#include <iostream>
#include <string>
#include "../helper.h"

auto readInput() {
    std::vector<std::vector<int>> result;
    auto lambda = [&](const std::string& line){
        auto parts = split(line, " ");
        std::vector<int> row;
        for (const auto& part : parts) {
            row.push_back(std::stoi(part));
        }
        result.push_back(row);
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();
    int size = 5;
    std::vector<int> lastRow(input[0].size() - (size - 1));
    std::fill(lastRow.begin(), lastRow.end(), 0);
    std::vector<int> currentRow(input[0].size() - (size - 1));
    for (int i = input.size() - 1; i >= 0; i--) {
        int sum = 0;
        for (int j = 0; j < (size - 1); j++) {
            sum += input[i][j];
        }
        for (int j = (size - 1); j < input[i].size(); j++) {
            sum += input[i][j];
            currentRow[j - (size - 1)] = sum;
            sum -= input[i][j - (size - 1)];
        }
        for (int j = 0; j < currentRow.size(); j++) {
            int max = lastRow[j];
            if (j - 1 >= 0)
                max = std::max(max, lastRow[j - 1]);
            if (j + 1 < currentRow.size()) 
                max = std::max(max, lastRow[j + 1]);
            currentRow[j] += max;
        }
        currentRow.swap(lastRow);
    }
    int max = 0;
    for (int entry : lastRow) {
        max = std::max(max, entry);
    }
    std::cout << max << std::endl;
    return 0;
}
