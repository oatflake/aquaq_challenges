#include <iostream>
#include <string>
#include "../helper.h"

class Dice {
private:
    int front;
    int left;
    int top;
public:    
    Dice(int front, int left, int top) : front(front), left(left), top(top) { }
    void rotateLeft() {
        int right = 7 - left;
        left = front;
        front = right;
    }
    void rotateRight() {
        int back = 7 - front;
        front = left;
        left = back;
    }
    void rotateUp() {
        int bottom = 7 - top;
        top = front;
        front = bottom;
    }
    void rotateDown() {
        int back = 7 - front;
        front = top;
        top = back;
    }
    static bool match(Dice& dice1, Dice& dice2) {
        return dice1.front == dice2.front;
    }
};

auto readInput() {
    std::string result;
    auto lambda = [&](auto line){
        result = line;
    };
    readInputFile(lambda);
    return result;
}

int main() {
    int sum = 0;
    auto input = readInput();
    std::array<Dice, 2> dices = { Dice(1,2,3), Dice(1,3,2) };
    for (int i = 0; i < input.length(); i++) {
        for (auto& dice : dices) {
            switch (input[i])
            {
            case 'L':
                dice.rotateLeft();
                break;
            case 'R':
                dice.rotateRight();
                break;
            case 'U':
                dice.rotateUp();
                break;
            case 'D':
                dice.rotateDown();
                break;
            default:
                break;
            }
        }
        sum += Dice::match(dices[0], dices[1]) ? i : 0;
    }
    std::cout << sum << std::endl;
    return 0;
}
