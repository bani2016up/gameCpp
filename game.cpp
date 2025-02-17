#include "game.hpp"
#include "mpc.hpp"
#include <ncurses.h>
#include <vector>
#include <random>

const int MAX_MPC = 10;


Game::Game(int fieldSize) : field(fieldSize) {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    currentTick = 0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::mt19937(seed);

    int mpc_amount = getRandomNumber(1, MAX_MPC);
    for (int i = 0; i < mpc_amount; i++) {
        int x = getRandomNumber(-15, 0);
        int y = getRandomNumber(0, field.getSize() - 1);
        if (takenByMPC.find(field.hashPosition(x, y)) == takenByMPC.end()) {
            aliveMPC.push_back(MPC(x, y));
            takenByMPC[field.hashPosition(x, y)] = true;
        }
    }
}


void Game::updateField(const int newX, const int newY) {
    this->field.setActiveCell(newX, newY);
    this->field.render(currentTick, this->getMPCs());
}

void Game::quit() {
    endwin();
    exit(EXIT_SUCCESS);
}

void Game::movePlayer(Direction direction) {
    int newX = field.getActiveX();
    int newY = field.getActiveY();

    switch (direction) {
        case UP:
            if (newX > 0) newX--;
            break;
        case DOWN:
            if (newX < field.getSize() - 1) newX++;
            break;
        case LEFT:
            if (newY > 0) newY--;
            break;
        case RIGHT:
            if (newY < field.getSize() - 1) newY++;
            break;
        case STOP:
            break;
    }

    updateField(newX, newY);
}

GameField& Game::getField() {
    return field;
}

void Game::nextTick(int tick) {
    if (anyMPCOutOfBounds()) {
        quit();
    }
    currentTick = tick;
    for (MPC& mpc : aliveMPC) {
        mpc.moveX(currentTick);
        field.checkForDeath(mpc);
    }
    int oldMpcCount = aliveMPC.size();
    aliveMPC.erase(
        std::remove_if(aliveMPC.begin(), aliveMPC.end(),
            [this](const MPC& mpc) {
                if (mpc.isDead()) {
                    takenByMPC.erase(field.hashPosition(mpc.getCurrentX(), mpc.getCurrentY()));
                    return true;
                }
                return false;
            }),
        aliveMPC.end()
    );
    if (aliveMPC.size() < oldMpcCount) {
        spawnMPC();
    }
    regenerateTakenByMPC();
}

void Game::spawnMPC() {
    int newMpcCount = getRandomNumber(1, MAX_MPC - aliveMPC.size());
    for (int i = 0; i < newMpcCount; i++) {
        int x = getRandomNumber(-15, 0);
        int y = getRandomNumber(0, field.getSize() - 1);
        if (takenByMPC.find(field.hashPosition(x, y)) == takenByMPC.end()) {
            aliveMPC.push_back(MPC(x, y));
            takenByMPC[field.hashPosition(x, y)] = true;
        }
    }

}
void Game::regenerateTakenByMPC(){
    takenByMPC.clear();
    for (const MPC& mpc : aliveMPC) {
        takenByMPC[field.hashPosition(mpc.getCurrentX(), mpc.getCurrentY())] = true;
    }
}

int Game::getRandomNumber(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

std::unordered_map<int, bool>& Game::getMPCs() {
    return takenByMPC;
}

bool Game::anyMPCOutOfBounds(){
    for (const MPC& mpc : aliveMPC) {
        if (mpc.getCurrentX() >= field.getSize()){
            return true;
        }
    }
    return false;
}
