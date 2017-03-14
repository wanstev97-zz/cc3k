#include <iostream>
#include <string>
#include "treasure.h"

Treasure::Treasure(int row, int col, std::string type, std::string name):
Item{row, col, type,name} {
  pick=true;
  if (name=="small"){
    value=1;
  } else if(name=="normal"){
    value=2;

  } else if(name=="merchant"){
    value=4;
  } else if(name=="dragon"){
    value=6;
    pick=false;
  }
}

Treasure::~Treasure(){}

bool pickAble(){
  return pick;
}

void isGone(){
  if (name=="dragon")
  {
    pick=true;
  }
}

void useGold(){
  curPlayer.setGold(curPlayer.getGold()+value);
  currentFloor->removeItem(row,col);
  action << "The player picked up $(value) gold" << endl;
}
