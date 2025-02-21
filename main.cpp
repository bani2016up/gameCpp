#include <ncurses.h>
#include "game.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <variant>

int TICK_INTERVAL = 1000;

const int TIME_INCREASE = -20;
const int MAP_INCREASE = 2;
const int MPCs_INCREASE = 2;

const int TICKS_TO_INCREASE_TIME = 20;
const int TICKS_TO_INCREASE_MAP = -1;
const int TICKS_TO_INCREASE_MPCs_COUNT = 10;

int timeCounter = TICKS_TO_INCREASE_TIME;
int mapCounter = TICKS_TO_INCREASE_MAP;
int mpcsCounter = TICKS_TO_INCREASE_MPCs_COUNT;




int main() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);


    if(has_colors() == FALSE) {
        endwin();
        std::cout << "Your terminal does not support color\n";
        return 1;
    }
    start_color();
    int fieldSize = 25;
    Game game(fieldSize);
    game.updateField(fieldSize/2, fieldSize/2);

    char ch;
    bool running = true;
    int currentTick = 0;
    auto lastTickUpdateTime = std::chrono::steady_clock::now();
    bool placeOnMove = false;

    game.getField().render(currentTick, game.getMPCs());
    refresh();

    while (running) {
        auto currentTime = std::chrono::steady_clock::now();
        int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTickUpdateTime).count();
        ch = getch();
        if (elapsedTime >= TICK_INTERVAL) {
            timeCounter --;
            mapCounter --;
            mpcsCounter --;
            currentTick++;
            lastTickUpdateTime = currentTime;
            game.nextTick(currentTick);
        }
        if (timeCounter == 0) {
            TICK_INTERVAL += TIME_INCREASE;
        }
        if (mapCounter == 0) {
            fieldSize += 1;
            game.scaleMap(MAP_INCREASE);
            mapCounter = TICKS_TO_INCREASE_MAP;
        }
        if (mpcsCounter == 0) {
            game.scaleMPCs(MPCs_INCREASE);
            mpcsCounter = TICKS_TO_INCREASE_MPCs_COUNT;
        }

        switch (ch) {
            case 'w':
                game.movePlayer(Direction::UP);
                break;
            case 's':
                game.movePlayer(Direction::DOWN);
                break;
            case 'a':
                game.movePlayer(Direction::LEFT);
                break;
            case 'd':
                game.movePlayer(Direction::RIGHT);
                break;
            case 'q':
                running = false;
                break;
            case ' ':
                game.getField().placeBomb(game.getField().getActiveX(), game.getField().getActiveY());
                break;
            case 'm':
                placeOnMove = !placeOnMove;
        }

        if (placeOnMove) {
            game.getField().placeBomb(game.getField().getActiveX(), game.getField().getActiveY());
        }
        game.getField().render(currentTick, game.getMPCs());
        napms(50);
    }

    game.quit();
    endwin();
    return 0;
}
