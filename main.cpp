#include <ncurses.h>
#include "game.hpp"
#include <iostream>
#include <chrono>

const int TICK_INTERVAL = 1000;


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
    int fieldSize = 15;
    Game game(fieldSize);
    game.updateField(fieldSize/2, fieldSize/2);

    char ch;
    bool running = true;
    int currentTick = 0;
    auto lastTickUpdateTime = std::chrono::steady_clock::now();

    game.getField().render(currentTick, game.getMPCs());
    refresh();

    while (running) {
        auto currentTime = std::chrono::steady_clock::now();
        int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTickUpdateTime).count();
        ch = getch();
        if (elapsedTime >= TICK_INTERVAL) {
            currentTick++;
            lastTickUpdateTime = currentTime;
            game.nextTick(currentTick);
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
            case 'b':
                game.getField().placeBomb(game.getField().getActiveX(), game.getField().getActiveY());
                break;
        }


        clear();
        game.getField().render(currentTick, game.getMPCs());
        refresh();
        napms(50);
    }

    game.quit();
    endwin();
    return 0;
}
