#include <iostream>
#include "field.hpp"

#pragma once
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
            newX += 1;
            break;
        case Direction::DOWN:
            newX -= 1;
            break;
        case Direction::LEFT:
            newY += 1;
            break;
        case Direction::RIGHT:
            newY -= 1;
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
