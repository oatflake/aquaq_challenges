#include <iostream>
#include <string>
#include "../helper.h"

//#define PRINT_DEBUG

struct RubicksCube {
    std::array<u_int8_t, 9> frontSide = { 1,1,1, 1,1,1, 1,1,1 };
    std::array<u_int8_t, 9> rightSide = { 4,4,4, 4,4,4, 4,4,4 };
    std::array<u_int8_t, 9> leftSide = { 3,3,3, 3,3,3, 3,3,3 };
    std::array<u_int8_t, 9> topSide = { 2,2,2, 2,2,2, 2,2,2 };
    std::array<u_int8_t, 9> bottomSide = { 5,5,5, 5,5,5, 5,5,5 };
    std::array<u_int8_t, 9> backSide = { 6,6,6, 6,6,6, 6,6,6 };     // backSide is mirrored vertically and horizontally
    
    void mirrorBackSideHorizontally() {
        for (int i = 0; i < 3; i++) {
            int tmp = backSide[i];
            backSide[i] = backSide[i + 2 * 3];
            backSide[i + 2 * 3] = tmp;
        }
    }

    void mirrorBackSideVertically() {
        for (int j = 0; j < 3; j++) {
            int tmp = backSide[j * 3];
            backSide[j * 3] = backSide[2 + j * 3];
            backSide[2 + j * 3] = tmp;
        }
    }

    void rotateClockWise(std::array<u_int8_t, 9>& side) {
        std::array<u_int8_t, 9> tmpCopy(side);
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                side[(2 - j) + i * 3] = tmpCopy[i + j * 3];
            }
        }
    }

    void rotateCounterClockWise(std::array<u_int8_t, 9>& side) {
        std::array<u_int8_t, 9> tmpCopy(side);
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                side[i + j * 3] = tmpCopy[(2 - j) + i * 3];
            }
        }
    }

    void rotateTopSideToTheFront() {
        mirrorBackSideHorizontally();
        std::array<u_int8_t, 9> tmp;
        frontSide.swap(tmp);
        topSide.swap(frontSide);
        backSide.swap(topSide);
        bottomSide.swap(backSide);
        tmp.swap(bottomSide);
        mirrorBackSideHorizontally();
        rotateClockWise(leftSide);
        rotateCounterClockWise(rightSide);
    }

    void rotateBottomSideToTheFront() {
        mirrorBackSideHorizontally();
        std::array<u_int8_t, 9> tmp;
        frontSide.swap(tmp);
        bottomSide.swap(frontSide);
        backSide.swap(bottomSide);
        topSide.swap(backSide);
        tmp.swap(topSide);
        mirrorBackSideHorizontally();
        rotateClockWise(rightSide);
        rotateCounterClockWise(leftSide);
    }

    void rotateLeftSideToTheFront() {
        mirrorBackSideVertically();
        std::array<u_int8_t, 9> tmp;
        frontSide.swap(tmp);
        leftSide.swap(frontSide);
        backSide.swap(leftSide);
        rightSide.swap(backSide);
        tmp.swap(rightSide);
        mirrorBackSideVertically();
        rotateClockWise(bottomSide);
        rotateCounterClockWise(topSide);
    }

    void rotateRightSideToTheFront() {
        mirrorBackSideVertically();
        std::array<u_int8_t, 9> tmp;
        frontSide.swap(tmp);
        rightSide.swap(frontSide);
        backSide.swap(rightSide);
        leftSide.swap(backSide);
        tmp.swap(leftSide);
        mirrorBackSideVertically();
        rotateClockWise(topSide);
        rotateCounterClockWise(bottomSide);
    }

    void rotateBackSideToTheFront() {
        rotateLeftSideToTheFront();
        rotateLeftSideToTheFront();
    }

public:
    void rotateFrontFaceClockWise() {
        rotateClockWise(frontSide);
        for (int i = 0; i < 3; i++) {
            int tmp = topSide[i + 2 * 3];
            topSide[i + 2 * 3] = leftSide[2 + (2 - i) * 3];
            leftSide[2 + (2 - i) * 3] = bottomSide[2 - i];
            bottomSide[2 - i] = rightSide[i * 3];
            rightSide[i * 3] = tmp;
        }
    }

    void rotateFrontFaceCounterClockWise() {
        rotateCounterClockWise(frontSide);
        for (int i = 0; i < 3; i++) {
            int tmp = topSide[i + 2 * 3];
            topSide[i + 2 * 3] = rightSide[i * 3];
            rightSide[i * 3] = bottomSide[2 - i];
            bottomSide[2 - i] = leftSide[2 + (2 - i) * 3];
            leftSide[2 + (2 - i) * 3] = tmp;
        }
    }

    void rotateLeftFaceClockWise() {
        print("inside rotateLeftFaceClockWise: before rotateLeftSideToTheFront");
        rotateLeftSideToTheFront();
        print("inside rotateLeftFaceClockWise: after rotateLeftSideToTheFront");
        rotateFrontFaceClockWise();
        print("inside rotateLeftFaceClockWise: after rotateFrontFaceClockWise");
        rotateRightSideToTheFront();
        print("inside rotateLeftFaceClockWise: after rotateRightSideToTheFront");
    }

    void rotateLeftFaceCounterClockWise() {
        print("inside rotateLeftFaceCounterClockWise: before rotateLeftSideToTheFront");
        rotateLeftSideToTheFront();
        print("inside rotateLeftFaceCounterClockWise: after rotateLeftSideToTheFront");
        rotateFrontFaceCounterClockWise();
        print("inside rotateLeftFaceCounterClockWise: after rotateFrontFaceCounterClockWise");
        rotateRightSideToTheFront();
        print("inside rotateLeftFaceCounterClockWise: after rotateRightSideToTheFront");
    }

    void rotateRightFaceClockWise() {
        print("inside rotateRightFaceClockWise: before rotateRightSideToTheFront");
        rotateRightSideToTheFront();
        print("inside rotateRightFaceClockWise: after rotateRightSideToTheFront");
        rotateFrontFaceClockWise();
        print("inside rotateRightFaceClockWise: after rotateFrontFaceClockWise");
        rotateLeftSideToTheFront();
        print("inside rotateRightFaceClockWise: after rotateLeftSideToTheFront");
    }

    void rotateRightFaceCounterClockWise() {
        print("inside rotateRightFaceCounterClockWise: before rotateRightSideToTheFront");
        rotateRightSideToTheFront();
        print("inside rotateRightFaceCounterClockWise: after rotateRightSideToTheFront");
        rotateFrontFaceCounterClockWise();
        print("inside rotateRightFaceCounterClockWise: after rotateFrontFaceCounterClockWise");
        rotateLeftSideToTheFront();
        print("inside rotateRightFaceCounterClockWise: after rotateLeftSideToTheFront");
    }

    void rotateTopFaceClockWise() {
        print("inside rotateTopFaceClockWise: before rotateTopSideToTheFront");
        rotateTopSideToTheFront();
        print("inside rotateTopFaceClockWise: after rotateTopSideToTheFront");
        rotateFrontFaceClockWise();
        print("inside rotateTopFaceClockWise: after rotateFrontFaceClockWise");
        rotateBottomSideToTheFront();
        print("inside rotateTopFaceClockWise: after rotateBottomSideToTheFront");
    }

    void rotateTopFaceCounterClockWise() {
        print("inside rotateTopFaceCounterClockWise: before rotateTopSideToTheFront");
        rotateTopSideToTheFront();
        print("inside rotateTopFaceCounterClockWise: after rotateTopSideToTheFront");
        rotateFrontFaceCounterClockWise();
        print("inside rotateTopFaceCounterClockWise: after rotateFrontFaceCounterClockWise");
        rotateBottomSideToTheFront();
        print("inside rotateTopFaceCounterClockWise: after rotateBottomSideToTheFront");
    }

    void rotateBottomFaceClockWise() {
        print("inside rotateBottomFaceClockWise: before rotateBottomSideToTheFront");
        rotateBottomSideToTheFront();
        print("inside rotateBottomFaceClockWise: after rotateBottomSideToTheFront");
        rotateFrontFaceClockWise();
        print("inside rotateBottomFaceClockWise: after rotateFrontFaceClockWise");
        rotateTopSideToTheFront();
        print("inside rotateBottomFaceClockWise: after rotateTopSideToTheFront");
    }

    void rotateBottomFaceCounterClockWise() {
        print("inside rotateBottomFaceCounterClockWise: before rotateBottomSideToTheFront");
        rotateBottomSideToTheFront();
        print("inside rotateBottomFaceCounterClockWise: after rotateBottomSideToTheFront");
        rotateFrontFaceCounterClockWise();
        print("inside rotateBottomFaceCounterClockWise: after rotateFrontFaceCounterClockWise");
        rotateTopSideToTheFront();
        print("inside rotateBottomFaceCounterClockWise: after rotateTopSideToTheFront");
    }

    void rotateBackFaceClockWise() {
        print("inside rotateBackFaceClockWise: before rotateBackSideToTheFront");
        rotateBackSideToTheFront();
        print("inside rotateBackFaceClockWise: after rotateBackSideToTheFront");
        rotateFrontFaceClockWise();
        print("inside rotateBackFaceClockWise: after rotateFrontFaceClockWise");
        rotateBackSideToTheFront();
        print("inside rotateBackFaceClockWise: after rotateBackSideToTheFront");
    }

    void rotateBackFaceCounterClockWise() {
        print("inside rotateBackFaceCounterClockWise: before rotateBackSideToTheFront");
        rotateBackSideToTheFront();
        print("inside rotateBackFaceCounterClockWise: after rotateBackSideToTheFront");
        rotateFrontFaceCounterClockWise();
        print("inside rotateBackFaceCounterClockWise: after rotateFrontFaceCounterClockWise");
        rotateBackSideToTheFront();
        print("inside rotateBackFaceCounterClockWise: after rotateBackSideToTheFront");
    }

    void print(const std::string& debugString) {
        #ifdef PRINT_DEBUG
        std::cout << debugString << std::endl;
        for (int j = 0; j < 3; j++) {
            std::cout << "   ";
            for (int i = 0; i < 3; i++) {
                std::cout << std::to_string(topSide[i + j * 3]);
            }
            std::cout << std::endl;
        }
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 3; i++) {
                std::cout << std::to_string(leftSide[i + j * 3]);
            }
            for (int i = 0; i < 3; i++) {
                std::cout << std::to_string(frontSide[i + j * 3]);
            }
            for (int i = 0; i < 3; i++) {
                std::cout << std::to_string(rightSide[i + j * 3]);
            }
            std::cout << std::endl;
        }
        for (int j = 0; j < 3; j++) {
            std::cout << "   ";
            for (int i = 0; i < 3; i++) {
                std::cout << std::to_string(bottomSide[i + j * 3]);
            }
            std::cout << std::endl;
        }
        for (int j = 0; j < 3; j++) {
            std::cout << "   ";
            for (int i = 0; i < 3; i++) {
                std::cout << std::to_string(backSide[i + j * 3]);
            }
            std::cout << std::endl;
        }
        #endif
    }

    int frontSideProduct() {
        int result = 1;
        for (int i : frontSide)
            result *= i;
        return result;
    }
};

auto readInput() {
    std::string result;
    auto lambda = [&](const std::string& line) {
        result = line;
    };
    readInputFile(lambda);
    return result;
}

int main() {
    auto input = readInput();    
    RubicksCube cube;
    
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == 'U') {
            if (i + 1 < input.length() && input[i + 1] == '\'') {
                cube.rotateTopFaceCounterClockWise();
            } else {
                cube.rotateTopFaceClockWise();
            }
        }
        if (input[i] == 'D') {
            if (i + 1 < input.length() && input[i + 1] == '\'') {
                cube.rotateBottomFaceCounterClockWise();
            } else {
                cube.rotateBottomFaceClockWise();
            }
        }
        if (input[i] == 'L') {
            if (i + 1 < input.length() && input[i + 1] == '\'') {
                cube.rotateLeftFaceCounterClockWise();
            } else {
                cube.rotateLeftFaceClockWise();
            }
        }
        if (input[i] == 'R') {
            if (i + 1 < input.length() && input[i + 1] == '\'') {
                cube.rotateRightFaceCounterClockWise();
            } else {
                cube.rotateRightFaceClockWise();
            }
        }
        if (input[i] == 'F') {
            if (i + 1 < input.length() && input[i + 1] == '\'') {
                cube.rotateFrontFaceCounterClockWise();
            } else {
                cube.rotateFrontFaceClockWise();
            }
        }
        if (input[i] == 'B') {
            if (i + 1 < input.length() && input[i + 1] == '\'') {
                cube.rotateBackFaceCounterClockWise();
            } else {
                cube.rotateBackFaceClockWise();
            }
        }
    }
    std::cout << cube.frontSideProduct() << std::endl;
    return 0;
}
