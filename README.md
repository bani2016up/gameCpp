
# 🎮 ZombieBomber: A Terminal-based Survival Game

## 🧟 Introduction

Welcome to ZombieBomber, an exciting terminal-based game where you defend your territory against encroaching zombies! As a lone survivor, you must strategically place bombs to eliminate the undead before they overrun your position. Can you survive the zombie apocalypse?

## 🕹️ Game Rules

1. **The Field**: You play on a square grid. The size of the grid is determined at the start of the game.
2. **Player Movement**:

   - W A S D to move up, right, down, left
   - Use B to plant a bomb
3. **Zombies (MPCs)**:

   - Zombies spawn randomly at the top side of the field.
   - They move from top to bottom across the field.
   - If any zombie reaches the bottom edge of the field, it's game over!
4. **Bombs**:

   - Place bombs to eliminate zombies.
   - Each bomb costs 10 points from your balance.
   - Bombs are stationary and detonate when a zombie moves onto them.
5. **Scoring**:

   - You start with 100 points.
   - Each zombie killed awards you 20 points.
   - Strategize to maintain a positive balance!
6. **Game Over**:

   - The game ends when a zombie reaches the bottom edge of the field.
   - Try to survive as many ticks (turns) as possible!

## 🚀 Getting Started

### Prerequisites

- C++ compiler (GCC or Clang recommended)
- CMake (version 3.0 or higher)
- ncurses library

### Building the Game

1. Clone this repository
2. ```
   cd gameCpp
   ```
3. ```
   cmake .
   ```
4. ```
   cmake --build .
   ```
5. ```
   ./cppGame
   ```
