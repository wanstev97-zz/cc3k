#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Player.h"
#include "item.h"
#include <string>


class Player;

class Enemy {
    bool isAlive = true;
    bool hasMoved = false;
    std::string type;
    std::string action;
    int hp;
    int atk;
    int def;
    int locationX;
    int locationY;
protected:
    int damageCalc();
public:
    Enemy(int y, int x);
    void refreshTurn();
    void attack(Player*);
    void move();
    std::string getType();
    int getLocationX();
    int getLocationY();
    void dies();
    virtual bool isHostile();
    virtual ~Enemy() = 0;
};

class NormalEnemy : public Enemy {
public:
    virtual int goldDrop();
};

class Human : public Enemy {
public:
    Human(int y, int x);
};

class Merchant : public Enemy {
    static bool isHostile;
public:
    bool makeHostile();
    void newGame();
    Merchant(int y, int x);
};

class Dragon : public Enemy {
    Item* hoard;
public:
    void notifyTreasure();
    Dragon(int y, int x, Item &i);
};

class Dwarf : public NormalEnemy {
public:
    Dwarf(int y, int x);
};

class Elf : public NormalEnemy {
public:
       Elf(int y, int x);
};

class Orcs : public NormalEnemy {
public:
    Orcs(int y, int x);
};

class Halfing : public NormalEnemy {
public:
    Halfing(int y, int x);
};

#endif
