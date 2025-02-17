#include "mpc.hpp"



MPC::MPC(int x, int y) : currentX(x), currentY(y), isDeadFlag(false), lastMoveTick(0) {}

void MPC::kill(){
    isDeadFlag = true;
}

void MPC::moveX(int& currentTick){
    currentX += 1;
}

int MPC::getCurrentX() const{
    return currentX;
}

int MPC::getCurrentY() const{
    return currentY;
}

bool MPC::isDead() const{
    return isDeadFlag;
}

bool MPC::operator==(const MPC& other) const {
    return (this->currentX == other.currentX) &&
           (this->currentY == other.currentY) &&
           (this->lastMoveTick == other.lastMoveTick) &&
           (this->isDeadFlag == other.isDeadFlag);
}
