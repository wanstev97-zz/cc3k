#include "Player.h"
#include <string>
#include <iostream>
#include "Floor.h"
#include "potion.h"
#include "Chamber.h"
#include "Enemy.h"
#include "item.h"
#include "potion.h"
#include "treasure.h"


using namespace std;

Player::Player(char c) {
    if (c == 's') {
        Shade newPlayer;
        newPlayer.beRace(this);
    }
    if (c == 'd') {
        Drow newPlayer;
        newPlayer.beRace(this);
    }
    if (c == 'v') {
        Vampire newPlayer;
        newPlayer.beRace(this);
    }
    if (c == 'g') {
        Goblin newPlayer;
        newPlayer.beRace(this);
    }
    if (c == 't') {
        Troll newPlayer;
        newPlayer.beRace(this);
    }

}

Player::~Player() {
}

void Player::goDirection(int inputRow, int inputCol, string dir) //helper function to travel in a direction
{
    if (dir == "no") {
        inputRow--;
    } else if (dir == "so") {
        inputRow++;
    } else if (dir == "ea") {
        inputCol++;
    } else if (dir == "we") {
        inputCol--;
    } else if (dir == "ne") {
        inputRow--;
        inputCol++;
    } else if (dir == "nw") {
        inputRow--;
        inputCol--;
    } else if (dir == "se") {
        inputRow++;
        inputCol++;
    } else if (dir == "sw") {
        inputRow++;
        inputCol--;
    }
};

void Player::playerAttack(Enemy *enemy, Floor* currentFloor) {
    //hit or miss phase
    bool hit = true;

    if (enemy->getType() == "Halfling") {
        int roll = rand() % 2;
        if (roll != 1) {
            hit = false; //atk misses
        }
    }
    //end of hit or miss phase

    if (hit == true) {
        //damage calculation phase
        int damage = (100 / (100 + enemy->getDef())) * atk;
        // getting the ceiling of damage
        if ((100 * atk) % (100 + enemy->getDef())) {
            damage++;
        }
        //end of damage calculation phase

        enemy->setHp(enemy->getHp() - damage); //does damage to enemy

        //hpSteal phase
        if (enemy->getType() == "Dwarf" && getRace() == "Vampire") {
            setHp(getHp() - hpSteal); //loses life
        } else {
            setHp(getHp() + hpSteal); //gain life effects on hit
        }
        //end of hpSteal phase

        if (enemy->getHp() < 0) //enemy died?
        {
            enemy->dies(currentFloor, this);
            setGold(getGold() + goldKill); //get extra gold on kills as ability
        }
    }
};

int Player::getHp() {
    return hp;
};

int Player::getAtk() {
    return atk;
};

int Player::getDef() {
    return def;
};

string Player::getRace() {
    return race;
};

void Player::setRace(string name) {
    race = name;
}

int Player::getGold() {
    return gold;
};

void Player::setGold(int amount) {
    gold = amount;
}

void Player::setLocation(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

void Player::move(string dir, Floor* currentFloor) {
    //check for if wall in the way
    int currentCol = col;
    int currentRow = row;

    goDirection(currentCol, currentRow, dir);
    int destinationWall = currentFloor->getWallAt(currentRow, currentCol);
    if (destinationWall == 1 || destinationWall == 2 || destinationWall == 6)//if walked into wall
    {
        action += "That's an invalid move";
        return;
    } else if (destinationWall == 7) {
        stairReached = true;
        floorsCompleted++;
        if (floorsCompleted == 5) {
            action += "You've won the game! Your score was $(getGold()*getMultiplier())";
            gameOver = true;
        } else {
            action += "You have arrived at the next floor";
        }

    } else //if move was valid
    {
        goDirection(col, row, dir);
        if (currentFloor->isItemAt(row, col)) //checks if picking up treasure
        {
            Item* currentItem = currentFloor->getItemAt(row, col);
            if (currentItem->getType() == "Treasure" || currentItem->pickAble()) {
                (currentFloor->getItemAt(row, col))->useGold();
            }
        }

        while (currentFloor->lookForEnemy(row, col) != NULL) //checks for surounding enemies and makes them attack if possible
        {
            Enemy *attackingEnemy = currentFloor->lookForEnemy(row, col);
            attackingEnemy->attack(this);
        }

        if (currentFloor->lookForPotion(row, col) != NULL) {
            Item *potionNearby = currentFloor->lookForPotion(row, col);
            if (potionNearby->getReveal()) {
                action += "You approach a $(potionNearby->getType()) potion";
            } else {
                action += "You approach an unknown potion";
            }
        } else {
            action += "You moved 1 space $(dir)";
        }
    }
};

void Player::usePot(string dir, Floor* currentFloor) {
    int posCol = col;
    int posRow = row;

    goDirection(posCol, posRow, dir);
    if (currentFloor->isItemAt(posRow, posCol)) {
        Item* usingPotion = currentFloor->getItemAt(posRow, posCol);
        if (usingPotion->getType() == "Potion") {
            usingPotion->usePotion();
            doneTurn = true;
            action += "The player used a $(usingPotion->getType()) potion";
        } else {
            action += "That's a treasure, not a potion!";
        }
    } else {
        action += "There's no potion there";
    }
};

void Player::attack(string dir, Floor* currentFloor) {
    int posCol = col;
    int posRow = row;

    goDirection(posCol, posRow, dir);
    if (currentFloor->isEnemyAt(posRow, posRow)) {
        playerAttack(currentFloor->getEnemyAt(posRow, posCol), currentFloor);
        doneTurn = true;
    } else //there's no enemy at location
    {
        action += "There's no enemy there";
    }
}

void Player::setHp(int amount) {
    hp = amount;
    if (hp > maxHp) //check for if over maxHp
    {
        hp = maxHp;
    }
    if (hp <= 0) {
        gameOver = true;
    }
}

void Player::setMaxHp(int amount) {
    maxHp = amount;
}

void Player::setAtk(int amount) {
    atk = amount;
}

void Player::setDef(int amount) {
    def = amount;
}

void Player::setPotFx(double amount) {
    potFx = amount;
}

void Player::setRegen(int amount) {
    regen = amount;
}

void Player::setHpSteal(int amount) {
    hpSteal = amount;
}

void Player::setGoldKill(int amount) {
    goldKill = amount;
}

void Player::setScoreMultiplier(double amount) {
    scoreMultiplier = amount;
}

void Player::changeAtk(int amount) {
    atk += amount;
}

void Player::changeDef(int amount) {
    def += amount;
}

void Player::refreshTurn() {
    doneTurn = false;
}
