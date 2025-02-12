#include <iostream>
#include "field.hpp"

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };


class Game {
private:
    GameField field;

    void updateField(const int newX, const int newY) {
        this->field.setActiveCell(newX, newY);
        this->field.updateDisplay();
    }


public:
    Game(int fieldSize = 4) : field(fieldSize) {
    }

    void quit() {
        std::cout << "Goodbye!" << std::endl;
        exit(0);
    }

    void movePlayer(Direction diraction){
        const int currentX = field.getActiveX();
        const int currentY = field.getActiveY();

        int newX = currentX;
        int newY = currentY;

        switch (diraction)
        {
        case Direction::UP:
            currentX + 1;
            break;
        case Direction::DOWN:
            currentX - 1;
            break;
        case Direction::LEFT:
            currentY + 1;
            break;
        case Direction::RIGHT:
            currentY - 1;
            break;
        case Direction::STOP:
            this->quit();
        default:
            break;
        }

        if (newX >= 0 && newX < field.getSize() && newY >= 0 && newY < field.getSize()) {
            updateField(newX, newY);
        }
    }

};
