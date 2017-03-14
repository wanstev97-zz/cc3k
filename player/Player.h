#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "Enemy.h"

class Enemy;
class Race;

class Player
{
  int maxHp,hp,atk,def,regen,hpSteal,goldKill;
  double potFx,scoreMultiplier;
  int gold=0;
  std::string race;
  bool doneTurn;
  void goDirection(int,int,std::string);
  void playerAttack(Enemy&);
  friend class Race;
public:
  Player(char);
  ~Player();
  int row,col;
  int getHp();
  int getAtk();
  int getDef();
  std::string getRace();
  void setRace(std::string);
  int getGold();
  double getMultiplier();
  void setLocation(int,int);
  void move(std::string dir);
  void usePot(std::string dir);
  void attack(std::string dir);
   void setMaxHp(int);
  void setHp(int);
  void setAtk(int);
  void setDef(int);
  void setPotFx(double);
  void setRegen(int);
  void setHpSteal(int);
  void setGoldKill(int);
  void setScoreMultiplier(double);
  void changeAtk(int amount);
  void changeDef(int amount);
  void refreshTurn();
};

#endif
