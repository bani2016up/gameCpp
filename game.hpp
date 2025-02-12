#ifndef GAME_HPP
#define GAME_HPP

#include "field.hpp"

class Game {
private:
    GameField field;

public:
    Game(int fieldSize = 4);

    void move();
    void start();
    void displayField() const;
    bool isGameOver() const;
};

#endif
