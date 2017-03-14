#include <cstdlib>
#include "Enemy.h"

using namespace std;

Enemy::Enemy(int y, int x) : locationX{x}, locationY{y}
{
}

Enemy::~Enemy() {
}

string Enemy::getType() {
    return type;
}

int getLocationX() {
    return locationX;
}

int getLocationY() {
    return locationY;
}

void refreshTurn() {
    hasMoved = false;
}

// Helper function for attack

int Enemy::damageCalc(Player &p) {
    const DAMAGE_FACTOR = 100;
    int damage = (DAMAGE_FACTOR / (DAMAGE_FACTOR + curPlayer.getDef)) * atk;
    // getting the ceiling of damage
    if ((DAMAGE_FACTOR * atk) % (DAMAGE_FACTOR + curPlayer.getDef)) {
        damage++;
    }
    return damae;
}

void Enemy::attack(Player* curPlayer) {
    int randInt = rand() % 2; // 50% chance attack misses

    // attack lands
    if (randInt == 1) {
        int damage = damageCalc(curPlayer);
        //Orcs does 50% more damage to Goblins
        if (type == "Orcs" && curPlayer.type == "Goblins") {
            const INCREASE_ATTACK = 1.5;
            damage = damage * INCREASE_ATTACK;
        }

        // updating player hp
        curPlayer.setHp(curPlayer.getHp() - damage);
        if (curPlayer.getHp() <= 0) {
            damage = damage + curPlayer.getHp();
            curPlayer.setHp(0);
            isAlive = false;
        }
        // attack misses
    } else {
        action.clear();
        action << type << " attacked and missed." << endl;
    }
    hasMoved = true;
}

void Enemy::move(Floor* currentFloor) {
    int x_change = 0;
    int y_change = 0;
    bool exit = false;

    while (!exit) {
        chance = rand() % 8;
        if (chance == 1) {
            x_change++;
        } else if (chance == 2) {
            y_change++;
        } else if (chance == 3) {
            x_change--;
        } else if (chance == 4) {
            y_change--;
        } else if (chance == 5) {
            x_change++;
            y_change++;
        } else if (chance == 6) {
            x_change++;
            y_change--;
        } else if (chance == 7) {
            x_change--;
            y_change--;
        } else if (chance == 8) {
            x_change--;
            y_change++;
        }

        // check if the location is out of bounds
        if (currentFloor.wallFloor[x + x_change][y + y_change] == 3) {
            x = x + x_change;
            y = Y + y_change;
        }

        hasMoved = true;
    }
}

bool Enemy::isHostile() {
    return true;
}

void Merchant::makeHostile() {
    Merchant::isHostile = true;
}

void Merchant::newGame() {
    Merchant::hostile = false;
}

bool Merchant::isHostile() {
    return Merchant::isHostile;
}

Merchant::isHostile = false;

Merchant::Merchant(int y, int x) : Enemy(y, x) {
    type = "Merchant";
    hp = 30;
    atk = 70;
    def = 5;
    isHostile = false;
}

Human::Human(int y, int x) : Enemy(y, x) {
    type = "Human";
    hp = 140;
    atk = 20;
    def = 20;
}

Dragon::Dragon(int y, int x, Item &i) : Enemy(y, x), hoard{i} {
    type = "Dragon";
    hp = 150;
    atk = 20;
    def = 20;
}

void Dragon::notifyTreasure() {
  hoard.isGone();
}

Dwarf::Dwarf(int y, int x) : Enemy(y, x) {
    type = "Dwarf";
    hp = 100;
    atk = 20;
    def = 30;
}

Elf::Elf(int y, int x) : Enemy(y, x) {
    type = "Elf";
    hp = 140;
    atk = 30;
    def = 10;
}

void Elf::attack() {
    const int NUMTURNS = 2;
    if (curPlayer.type != "Drow") {
        for (int i = 0; i < NUMTURNS; i++) {
            super.attack();
        }
    } else {
        super.attack();
    }
}

Orcs::Orcs(int y, int x) : Enemy(y, x) {
    type = "Orcs";
    hp = 180;
    atk = 30;
    def = 25;
}

Halfling::Halfling(int y, int x) : Enemy(y, x) {
    type = "Halfling";
    hp = 100;
    atk = 15;
    def = 20;
}

void Enemy::dies() {
    if (type == "Dragon") {
        notifyTreasure();
    } else if (type == "Human") {
        Item = new Treasure(y, x, "Human");
    } else if (type == "Merchant") {
        Item = new Treasure(y, x, "Merchant");
    } else {
        curPlayer.setGold(curPlayer.getGold()+ goldDrop());
    }
}

int NormalEnemy::goldDrop() {
    const int small = 1;
    const int normal = 2;
    int gold = rand() % 2;
    if (gold == 1) {
        return small;
    } else {
        return normal;
    }
}
