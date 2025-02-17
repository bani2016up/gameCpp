#include "field.hpp"
#include <ncurses.h>
#include <unordered_set>
#include <string>
#include "mpc.hpp"

enum CellState { EMPTY, NONE_EMPTY, BOMB };

const char EMPTY_SIGN = '.';
const char PLAYER_SIGN = 'X';
const char BOMB_SIGN = '*';
const char PLAYER_ON_BOMB_SIGN = 'O';
const char ZOMBIE_SIGN = '+';
const char DEATH_SIGN = '$';

const int INITAL_BALANCE = 100;
const int BOMB_COST = 10;
const int KILL_PRICE = 20;

const int HUD_OFFSET_X = 2;

const std::string RED_MODIFED = "\x1b[31m";


GameField::GameField(int fieldSize) : size(fieldSize), activeX(0), activeY(0), nonActiveSize(fieldSize / 3), activeBalance(INITAL_BALANCE), placed_bombs(std::unordered_set<int> {}) {}

int GameField::hashPosition(int x, int y) const
{
    return x * size + y;
}


int GameField::getSize() const
{
    return size;
}

int GameField::getActiveX() const
{
    return activeX;
}

int GameField::getActiveY() const
{
    return activeY;
}

void GameField::render(int& tick, std::unordered_map<int, bool>& zombies) const
{
    clear();
    renderNonActiveCells(zombies);
    renderActiveCells(zombies);
    renderHUD(tick);
    refresh();
}

void GameField::renderHUD(int& tick) const
{
    mvprintw(0, 0, "Balance: (%d), Tick: (%d)", activeBalance, tick);
}

void GameField::renderNonActiveCells(std::unordered_map<int, bool>& zombies) const
{
    attron(COLOR_PAIR(1));
    for (int x = 0; x < nonActiveSize; ++x)
    {
        for (int y = 0; y < size; ++y)
        {
            bool isZombieCell = zombies.find(hashPosition(x - nonActiveSize, y))!= zombies.end();
            if (isZombieCell) {
                mvaddch(x + HUD_OFFSET_X, y * 2, ZOMBIE_SIGN | COLOR_PAIR(1));
            }
            else {
                mvaddch(x+HUD_OFFSET_X, y * 2, EMPTY_SIGN);
            }
        }
    }
    attroff(COLOR_PAIR(1));
}

void GameField::renderActiveCells(std::unordered_map<int, bool>& zombies) const
{
    attron(COLOR_PAIR(2));
    for (int x = 0; x < size; ++x)
    {
        for (int y = 0; y < size; ++y)
        {
            bool isBombCell = placed_bombs.find(hashPosition(x, y)) != placed_bombs.end();
            bool isPlayerCell = (x == activeX && y == activeY);
            bool isZombieCell = zombies.find(hashPosition(x, y))!= zombies.end();

            if (isBombCell & isPlayerCell) {
                mvaddch(x + HUD_OFFSET_X + nonActiveSize, y * 2, PLAYER_ON_BOMB_SIGN | COLOR_PAIR(1));
            }
            else if (isZombieCell) {
                mvaddch(x + HUD_OFFSET_X + nonActiveSize, y * 2, ZOMBIE_SIGN);
            }
            else if (isBombCell) {
                mvaddch(x + HUD_OFFSET_X + nonActiveSize, y * 2, BOMB_SIGN | COLOR_PAIR(1));
            }
            else if (isPlayerCell) {
                mvaddch(x + HUD_OFFSET_X + nonActiveSize, y * 2, PLAYER_SIGN);
            }
            else
            {
                mvaddch(x + HUD_OFFSET_X + nonActiveSize, y * 2, EMPTY_SIGN);
            }
        }
    }
    attroff(COLOR_PAIR(2));
}

void GameField::setActiveCell(int x, int y)
{
    activeX = x;
    activeY = y;
}

void GameField::placeBomb(int x, int y)
{
    int future_balance = activeBalance - BOMB_COST;
    if (future_balance < 0) {
        return;
    }
    placed_bombs.insert(hashPosition(x, y));
    activeBalance = future_balance;
}

void GameField::checkForDeath(MPC& mpc){
    if (placed_bombs.find(hashPosition(mpc.getCurrentX(), mpc.getCurrentY()))!= placed_bombs.end()) {
        mpc.kill();
        placed_bombs.erase(hashPosition(mpc.getCurrentX(), mpc.getCurrentY()));
        activeBalance += KILL_PRICE;
    }

}

int GameField::getActiveBalance() const {
    return activeBalance;
}
