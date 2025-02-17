#ifndef MPC_HPP
#define MPC_HPP


class MPC {
private:
    int currentX;
    int currentY;
    int lastMoveTick;
    bool isDeadFlag;

public:
    MPC(int, int);
    bool operator==(const MPC& other) const;

    void kill();
    void moveX(int&);
    int getCurrentX() const;
    int getCurrentY() const;
    bool isDead() const;


};

#endif
