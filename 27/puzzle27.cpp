#include <iostream>
#include <string>
#include <unordered_set>
#include <memory>
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

struct Visitor {
    virtual void visit(std::string& grid, int x, int y, int width, int height) = 0;
};

struct GetTailCoord : public Visitor {
    int x;
    int y;
    virtual void visit(std::string& grid, int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
    };
};

struct GetValue : public Visitor {
    int lastX;
    int lastY;
    int dirX = 0;
    int dirY = 0;
    std::string currentWord = "";

    GetValue(int x, int y) : lastX(x), lastY(y) {}
    
    int wordValue() {
        int value = 0;
        for (char c : currentWord) {
            value += c - 'a' + 1;
        }
        return value * currentWord.length();
    }
    
    virtual void visit(std::string& grid, int x, int y, int width, int height) {
        int newDirX = x - lastX;
        int newDirY = y - lastY;
        if ((newDirX != dirX || newDirY != dirY) && dirX + dirY != 0) {
            totalValue += wordValue();
            char lastChar = currentWord.back();
            currentWord = "";
            currentWord += lastChar;
        }
        currentWord += grid[x + y * width];
        this->lastX = x;
        this->lastY = y;
        this->dirX = newDirX;
        this->dirY = newDirY;
    };

    int getTotalValue() {
        return this->totalValue + this->wordValue();
    }
private:
    int totalValue = 0;
};

struct DeleteSnake : Visitor {
    virtual void visit(std::string& grid, int x, int y, int width, int height) {
        grid[x + y * width] = ' ';
    }
};

void followSnake(std::string& grid, int x, int y, int width, int height, std::shared_ptr<Visitor> visitor) {
    char c = grid[x + y * width];
    std::unordered_set<int> visited;
    std::array<std::tuple<int, int>, 4> deltas = { std::make_tuple(-1, 0), {1, 0}, {0, -1}, {0, 1} };
    bool moving = true;
    while (moving) {
        moving = false;
        visited.insert(x + y * width);
        visitor->visit(grid, x, y, width, height);
        for (auto [dx, dy] : deltas) {
            int x1 = x + dx;
            int y1 = y + dy;
            if (x1 < 0 || x1 >= width || y1 < 0 || y1 >= height)
                continue;
            int i = x1 + y1 * width;
            if (grid[i] != ' ' && visited.find(i) == visited.end()) {
                x = x1;
                y = y1;
                moving = true;
                break;
            }
        }
    }
}

int main() {
    int result = 0;
    auto [grid, width, height] = readInput();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[x + y * width] != ' ') {
                auto tailCoord = std::make_shared<GetTailCoord>();
                followSnake(grid, x, y, width, height, tailCoord);
                auto getValue = std::make_shared<GetValue>(tailCoord->x, tailCoord->y);
                followSnake(grid, tailCoord->x, tailCoord->y, width, height, getValue);
                auto deleteSnake = std::make_shared<DeleteSnake>();
                followSnake(grid, tailCoord->x, tailCoord->y, width, height, deleteSnake);
                result += getValue->getTotalValue();
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}
