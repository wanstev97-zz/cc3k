#ifndef __FACTORY_H__
#define __FACTORY_H__
#include <string>
#include <vector>
#include <utility>
#include "Chamber.h"
#include "item.h"
#include "Enemy.h"
#include <memory>

class Treasure;
class Potion;
class Enemy;

class Factory{
	int pcplace;
	std::shared_ptr<Chamber> c;
public:
	Factory(std::shared_ptr<Chamber>);
	~Factory();
	std::shared_ptr<Potion> GeneratePotion();
	std::shared_ptr<Treasure> GenerateTreasure();
	std::shared_ptr<Enemy> GenerateEnemy();
	std::shared_ptr<Player> GeneratePlayer();
	std::vector<std::pair<int,int>> GenerateStairs();
	std::shared_ptr<Enemy> GenerateDragon(int x,int y,Treasure *dragon);
};

#endif
