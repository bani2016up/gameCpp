#include <iostream>
#include "field.hpp"

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };


class Game {
private:
    GameField field;

    int playerX = 0;
    int playerY = 0;

    void updateField(const int newX, const int newY) {

    }


public:
    Game(int fieldSize = 4) : field(fieldSize) {
    }

    void move(Direction diraction){

    }

};
