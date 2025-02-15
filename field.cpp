#include <iostream>
#include <vector>

const std::string EMPTY_SIGN = "-";
const std::string NONE_EMPTY_SIGN = "X";


class GameField {
private:
    int size;

    int activeX = 0;
    int activeY = 0;

    void clearCls() const {
        // Clear terminal screen (Linux/Mac)
        std::cout << "\033[2J\033[1;1H";
    }

public:
    GameField(int fieldSize) : size(fieldSize) {}

    int getSize() const {
        return size;
    }
    int getActiveX() const {
        return activeX;
    }
    int getActiveY() const {
        return activeY;
    }

    void updateDisplay() const {
        this->clearCls();
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                if (x == activeX && y == activeY) {
                    std::cout << NONE_EMPTY_SIGN;
                } else {
                    std::cout << EMPTY_SIGN;
                }
            }
            std::cout << std::endl;
        }
    }

    void setActiveCell(int x, int y) {
        this->activeX = x;
        this->activeY = y;
    }
};
