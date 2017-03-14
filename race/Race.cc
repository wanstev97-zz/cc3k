#include <iostream>

#include "Race.h"

using namespace std;

Race::Race(string name,int maxHp, int hp,int atk,int def,double potFx,int regen,int hpSteal, int goldKill, double scoreMultiplier):
name{name},maxHp{maxHp},hp{hp},atk{atk},def{def},potFx{potFx},regen{regen},hpSteal{hpSteal},goldKill{goldKill},scoreMultiplier{scoreMultiplier}{}
void Race::beRace(Player &p)
{
  //set all of the player's values to that of the race they chose
    p.setRace(name);
    p.setMaxHp(maxHp);
    p.setHp(hp);
    p.setAtk(atk);
    p.setDef(def);
    p.setPotFx(potFx);
    p.setRegen(regen);
    p.setHpSteal(hpSteal);
    p.setGoldKill(goldKill);
};

Shade::Shade():Race{"Shade",125,125,25,25,1,0,0,0,1.5}{}

Drow::Drow():Race{"Drow",150,150,25,15,1.5,0,0,0,1}{}

Vampire::Vampire():Race{"Vampire",2147483647,50,25,25,1,0,5,0,1}{}

Troll::Troll():Race{"Troll",120,120,25,15,1,5,0,0,1}{}

Goblin::Goblin():Race{"Goblin",110,110,15,20,1,0,0,5,1}{}
