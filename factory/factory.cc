#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "factory.h"

using namespace std;
Factory::Factory(shared_ptr<Chamber> c):
 c{c}{}

Factory::~Factory(){}


shared_ptr<Potion> GeneratePotion(){
	int numchamber= rand()%5;
	int numpotion= rand()%6;
	vector<pair<int,int>> pos =c[numchamber]->getPosition();
	int x=pos.first;
    int y=pos.second;
	if (numpotion==0){
		return make_shared<Potion>(x,y,"Potion","RH");
	}
	if (numpotion==1){
		return make_shared<Potion>(x,y,"Potion","BA");
	}
	if (numpotion==2){
		return make_shared<Potion>(x,y,"Potion","BD");
	}
	if (numpotion==3){
		return make_shared<Potion>(x,y,"Potion","PH");
	}
	if (numpotion==4){
		return make_shared<Potion>(x,y,"Potion","WA");
	}
	if (numpotion==5){
		return make_shared<Potion>(x,y,"Potion","WD");
	}
}


shared_ptr<Treasure> GenerateTreasure(){
	int numchamber= rand()%5;
	int numTreasure= rand()%7;
	vector<pair<int,int>> pos =c[numchamber]->getPosition();
	int x=pos.first;
    int y=pos.second;
	if (numTreasure<=4){
		return make_shared<Treasure>(x,y,"Gold","normal");
	}
	if (numTreasure<=6){
		return make_shared<Treasure>(x,y,"Gold","small");
	}
	if (numTreasure<=8){
		return make_shared<Treasure>(x,y,"Gold","dragon");
	}

}

shared_ptr<Enemy> GenerateEnemy(){
	int numchamber= rand()%5;
	int numEnemy=rand()%18;
	vector<pair<int,int>> pos =c[numchamber]->getPosition();
	int x=pos.first;
    int y=pos.second;
	if(numEnemy>=0||numEnemy<=3){
		return make_shared<Human>(x,y);
	}
	if(numEnemy>=4||numEnemy<=6){
		return make_shared<Dwarf>(x,y);
	}
	if(numEnemy>=7||numEnemy<=11){
		return make_shared<Halfling>(x,y);
	}
	if(numEnemy>=12||numEnemy<=13){
		return make_shared<Elf>(x,y);
	}
	if(numEnemy>=14||numEnemy<=15){
		return make_shared<Elf>(x,y);
	}
	if(numEnemy>=16||numEnemy<=17){
		return make_shared<Merchant>(x,y);
	}

}


shared_ptr<Player> GeneratePlayer(){
	int numchamber= rand()%5;
	pcplace=numchamber;
    vector<pair<int,int>> pos =c[numchamber]->getPosition();
    int x=pos.first;
    int y=pos.second;
	auto p= make_shared<Player>();
	p->setLocation(x,y);
	return p;
}


vector<pair<int,int>> GenerateStairs(){
	int numchamber= rand()%5;
	vector<pair<int,int>> pos =c[numchamber]->getPosition();
	int x=pos.first;
    int y=pos.second;
	if(pcplace!=numchamber){
		return {x,y};
	} else{
		GenerateStairs();
	}

}

shared_ptr<Enemy> GenerateDragon(int x,int y,Treasure *dragon){
	
	return make_shared<Dragon>(x,y,dragon);
}