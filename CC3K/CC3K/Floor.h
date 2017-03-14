#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Chamber.h"
#include "Enemy.h"
#include "factory.h"
#include "item.h"
#include "potion.h"
#include "treasure.h"
#include "Player.h"
#include "Race.h"

class Enemy;

class Floor
{
  std::string mapSeed;
  int** wallFloor; //NOTE is this how to declare smart pointers???
  Item** itemFloor;
  bool** itemThereFloor;
  Enemy** enemyFloor;
  bool** enemyThereFloor;
  std::vector<Treasure*> dragonHoards;
  int floorCount=1;


public:
  Floor();
  Floor(std::string);
  ~Floor();

  Treasure* lookForHoard(int,int);
  Enemy* lookForEnemy(int,int);
  Potion* lookForPotion(int,int);

  int getWallAt(int,int);
  bool isItemAt(int,int);
  Item* getItemAt(int,int);
  bool isEnemyAt(int,int);
  Enemy* getEnemyAt(int,int);
  void removeItem(int,int);
  void removeEnemy(int,int);
  void dropTreasureAt(int,int);

  void placeDragon(int,int);

  void floorAfterTurn(Player *);
  void enemyMovePhase();
  void startTurn();
};

#endif
