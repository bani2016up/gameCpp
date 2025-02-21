#ifndef GAME_HPP
#define GAME_HPP

#include "field.hpp"
#include <vector>
#include "mpc.hpp"
#include <chrono>
#include <unordered_map>
#include <random>

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };

class Game {
private:
    GameField field;
    int currentTick;
    std::mt19937 rng;
    std::vector<MPC> aliveMPC;
    std::unordered_map<int, bool> takenByMPC;

    int getRandomNumber(int, int);
    void regenerateTakenByMPC();
    bool anyMPCOutOfBounds();
    void spawnMPC();

public:
    Game(int fieldSize);
    void updateField(const int newX, const int newY);
    void quit();
    void movePlayer(Direction direction);
    GameField& getField();
    void nextTick(int);
    std::unordered_map<int, bool>& getMPCs();
    void scaleMap(int);
    void scaleMPCs(int);
};


#endif
