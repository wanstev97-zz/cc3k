#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Player.h"
#include "item.h"
#include "treasure.h"
#include "Floor.h"
#include <string>
#include "global.h"

class Player;


class Enemy {
  bool isAlive = true;
  bool hasMoved = false;

  int locationY;
  int locationX;

protected:
  int damageCalc(Player*);
  int hp;
  int atk;
  int def;
  std::string type;

public:
  Enemy(int y, int x);
  void refreshTurn();
  void attack(Player*);
  void move(Floor*);
  std::string getType();
  int getLocationX();
  int getLocationY();
  int getDef();
  int getHp();
  void setHp(int);
  void dies(Floor *, Player *);
  virtual void notifyTreasure();
  virtual int goldDrop();
  virtual bool isHostile();
  virtual ~Enemy() = 0;
};

class NormalEnemy : public Enemy {
public:
  NormalEnemy(int y, int x);
  virtual int goldDrop();
};

class Human : public Enemy {
public:
  Human(int y, int x);
};

class Merchant : public Enemy {
  static bool hostile;

public:
  bool isHostile();
  void makeHostile();
  Merchant(int y, int x);
};

class Dragon : public Enemy {
  Item* hoard;
public:
  void notifyTreasure();
  Dragon(int y, int x, Item *i);
};

class Dwarf : public NormalEnemy {
public:
  Dwarf(int y, int x);
};

class Elf : public NormalEnemy {
public:
  Elf(int y, int x);
  void attack(Player*);
};

class Orcs : public NormalEnemy {
public:
  Orcs(int y, int x);
};

class Halfling : public NormalEnemy {
public:
  Halfling(int y, int x);
};

#endif
