#include <iostream>
#include <vector>

const std::string EMPTY_SIGN = "-";
const std::string NONE_EMPTY_SIGN = "X";


class GameField {
private:
    int size;

    int activeX = 0;
    int activeY = 0;


public:
    GameField(int fieldSize) : size(fieldSize) {}

    int getSize() const {
        return size;
    }

    void display() const {
    }


    void setActiveCell(int x, int y) {
        this->activeX = x;
        this->activeY = y;
    }
};
