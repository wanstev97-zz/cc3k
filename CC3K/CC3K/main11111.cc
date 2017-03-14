#include <iostream>
#include <string>
#include <memory>
#include <fstream>

using namespace std;
#include "Floor.h"
#include "Player.h"
#include "Race.h"


int floorsCompleted=0;
string action;
int whereToStart=0;
bool stairReached;
char raceInput;

void printInfo(Player* curPlayer) {
    cout << "Race: " << curPlayer->getRace() << " Gold: " << curPlayer->getGold();
    for (int i = 0; i < 50; i++) {
        cout << " ";
    }
    cout << "Floor " << floorsCompleted << endl;
    cout << "HP: " << curPlayer->getHp() << endl;
    cout << "Atk: " << curPlayer->getAtk() << endl;
    cout << "Def: " << curPlayer->getDef() << endl;
    cout << "Action: " << action;
}

void nextFloor(Floor* currentFloor)
{
  Floor* temp=currentFloor;
  delete temp;
  currentFloor= new Floor(MAP_FILE);
}
void printCommand() {
    cout << "Enter a valid command: " << endl;
    cout << "Change direction: no, so, ea, we, ne, se, sw, nw" << endl;
    cout << "Use potion: u <direction>" << endl;
    cout << "Attack enemy: a <direction>" << endl;
    cout << "Stop/Allow enemy movement: f" << endl;
    cout << "Restart the game: r" << endl;
    cout << "Quit: q" << endl;
}

char createPlayer() {
    while (true) {
        string input;

        // Choosing a player
        cout << "Choose a race for the player:" << endl;
        cout << "Shade: 125 HP, 25 ATK, 25 DEF" << endl;
        cout << "\tEffect: Score increases by 50%" << endl;
        cout << "Drow: 150 HP, 25 ATK, 15 DEF" << endl;
        cout << "\tEffect: All potions are magnified by 1.5" << endl;
        cout << "Vampire: 50 HP, 25 ATK, 25 DEF" << endl;
        cout << "\tEffect: Gains 5 HP every successful attack "
                << "(loses 5 HP from Dwarfs) and no maximum HP" << endl;
        cout << "Troll: 120 HP, 25 ATK, 15 DEF" << endl;
        cout << "\tEffect: Regains 5 HP every turn; HP is capped at 120 HP" << endl;
        cout << "Goblin: 110 HP, 15 ATK, 20 DEF" << endl;
        cout << "\tEffect: Steals 5 gold from every slain enemy" << endl;
        cout << "Type: s for shade, d for drow, v for vampire, "
                << "t for troll, and g for goblin" << endl;
        cin >> input;
        raceInput=input;

        // Creating player
        if (input == "s" || input == "d" || input == "v"
                || input == "t" || input == "g") {
            return input.at(0);
        } else {
            cout << "Please make a valid selection." << endl;
        }
    }
}

void usePotion(Player* curPlayer) {
    string dir;
    cin >> dir;

    if (dir == "no"||dir=="ea"||dir=="so"||dir=="we"||dir=="ne"||dir=="se"||dir=="sw"||dir=="nw") {
      curPlayer->usePot(dir);
    } else {
        cout << "Invalid direction" << endl;
    }

}

void attackEnemy(Player* curPlayer) {
    string dir;
    cin >> dir;

    if (dir == "no"||dir=="ea"||dir=="so"||dir=="we"||dir=="ne"||dir=="se"||dir=="sw"||dir=="nw") {
      curPlayer->attack(dir);
    } else {
        cout << "Invalid direction" << endl;
    }
}

void restar(Player* curPlayer, Floor* currentFloor){
    delete currentFloor; // floor = nullptr
    delete curPlayer; // player = nullptr
}

int playerCommand(Player* curPlayer, Floor* currentFloor) {
    string input;
    while (true) {
        printCommand();
        cin >> input;
        if (input == "no" || input == "so" || input == "ea" || input == "we" ||
                input == "ne" || input == "se" || input == "sw" || input == "nw") {//move player

            curPlayer->move(input);
            return 0;
        } else if (input == "u") { // use potion
            usePotion(curPlayer);
            currentFloor->floorAfterTurn(curPlayer);
            return 0;
        } else if (input == "a") { // attack enemy
            attackEnemy(curPlayer);
            currentFloor->floorAfterTurn(curPlayer);
            return 0;
        } else if (input == "r") { // restart game
            restar(curPlayer,currentFloor);
            return 1;
        } else if (input == "q") { // quit
            return 2;
        } else if (input =="f"){
            return 3;
        }else {
            cout << "Please enter valid input" << endl;
        }
    }
}


int main(int argc, char *argv[]) {
    srand(time(nullptr));
    const string MAP_FILE = "map.txt";
    bool exit = false;
    bool gameOver = false;
    bool stopEnemyMovement = false;
    string input;
    cout << "Welcome to ChamberCrawler3000!" << endl;

    // Start new game
    while (true) {
        gameOver = false;
        exit = false;
        stopEnemyMovement = false;
        auto curPlayer = new Player(createPlayer());
        auto currentFloor = new Floor(MAP_FILE);

        cout << endl;
        currentFloor->floorAfterTurn(curPlayer);
        printInfo(curPlayer);
        cout << "Player has been spawned" << endl;

        while (true) {
            currentFloor->startTurn();
            int command = playerCommand(curPlayer,currentFloor);
            if (command == 0){
                printInfo(curPlayer);
            }else if (command == 1) {
                restar(curPlayer,currentFloor);
                break;
            } else if (command == 2) {
                exit = true;
                break;
            } else if (command ==3){
                stopEnemyMovement = !stopEnemyMovement;
            }

            //Stop enemies from moving
            if (!stopEnemyMovement){
                currentFloor->enemyMovePhase();
            }

            if (stairReached)
            {
              nextFloor(currentFloor,MAP_FILE);
            }

            if (gameOver){
                while (true) {
                    cout << "Play again? (Y/N)" << endl;
                    cin >> input;
                    if (input == "N") {
                        cout << "Thanks for playing!" << endl;
                        exit = true;
                        break;
                    } else if (input == "Y") {
                        break;
                        }else{

                        cout << "Please enter a valid commmand." << endl;
                    }
                }
            }

            currentFloor->floorAfterTurn(curPlayer);
            printInfo(curPlayer);
        }
    if (exit) {
        break;
    }
   }
  return 0;
}
