#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <string>

const std::string EMPTY_SIGN = "-";
const std::string NONE_EMPTY_SIGN = "X";

typedef std::vector<bool> row;

class GameField {
private:
    int size;
    std::vector<row> field;

    void clearScreen() const;

public:
    GameField(int fieldSize);
    int getSize() const;
    void updateDisplay() const;
    void setActiveCell(int, int);
    int getActiveX() const;
    int getActiveY() const;
};

#endif
