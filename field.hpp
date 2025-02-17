#ifndef FIELD_HPP
#define FIELD_HPP

#include <string>
#include <unordered_set>
#include "mpc.hpp"

extern const char EMPTY_SIGN;
extern const char PLAYER_SIGN;

class GameField {
private:
    int size;
    int activeX;
    int activeY;
    int nonActiveSize;
    int activeBalance;
    std::unordered_set<int> placed_bombs;

    void renderNonActiveCells(std::unordered_map<int, bool>&) const;
    void renderActiveCells(std::unordered_map<int, bool>&) const;
    void renderHUD(int&) const;

public:
    GameField(int fieldSize);
    int hashPosition(int, int) const;
    int getSize() const;
    int getActiveX() const;
    int getActiveY() const;
    void render(int&, std::unordered_map<int, bool>&) const;
    void setActiveCell(int, int);
    void placeBomb(int, int);
    void checkForDeath(MPC&);
    int getActiveBalance() const;
};

#endif
