#include "Floor.h"
#include <vector>
#include <utility>
using namespace std;

int** Floor::wallFloor=(new int[25][79]); //implement these with smart pointers
// 1 is -, 2 is |, 3 is . (floor), 4 is + (door), 5 is # (passage), 6 is space, 7 is stairs

Item** Floor::itemFloor=(new Item*[25][79]);
bool** Floor::itemThereFloor=(new bool[25][79])=false;
Enemy** Floor::enemyFloor=(new Enemy*[25][79]);
bool** Floor::enemyThereFloor=(new bool[25][79])=false;

void Floor::Floor()
{
  /*
  //NOTE
  //calls and declares 5 chambers to be located with shared_ptr chamberList
  auto chamberList=make_shared<Chamber[5]> ();
  for (int x=1; x<=5; x++)
  {
  chamberList[x]=Chamber(x);
}

Factory currentFloorFactory(chamberList);
Item generatedPotion,generatedTreasure;
Enemy generatedEnemy;
int row, col;

playerPtr<Player>= (new Player());

row=(currentFloorFactory).GenerateStairs()).second;//second is the y value, first is the x value
col=(currentFloorFactory).GenerateStairs()).first;

wallFloor[row][col]=7;
//NOTE generation of the wallFloor



for (int x=0;x<10;x++)
{
generatedPotion=currentFloorFactory.GeneratePotion();
row=generatedPotion.getRow();
col=generatedPotion.getCol();
itemThereFloor[row][col]=true;
itemFloor[row][col]=generatedPotion;
}

for (int x=0;x<10;x++)
{
generatedTreasure=currentFloorFactory.GenerateTreasure();
row=generatedTreasure.getRow();
col=generatedTreasure.getCol();
itemThereFloor[row][col]=true;
itemFloor[row][col]=generatedTreasure
if (generatedTreasure.getType()=="dragon")
{
dragonHoards.push_back(&generatedTreasure);
}
}

for (int x=0;x<20;x++)
{
generatedEnemy=currentFloorFactory.GenerateEnemy();
row=generatedEnemy.getLocationX();
col=generatedEnemy.getLocationY();
enemyThereFloor[row][col]=true;
enemyFloor[row][col]=generatedEnemy;
}

for (int x=0;x<dragonHoards.size();x++) //places all dragons in relation to their hoards
{
placeDragon(dragonHoards[x]);
}
*/
}

Floor::Floor(string mapFile)
{
  mapSeed=mapFile;
  ifstream input("$(mapFile)");  //  The input file

  for(int x=0;x<79;x++)
  {
    for (int y=0;y<25;y++)
    {
      // 1 is -, 2 is |, 3 is . (floor), 4 is + (door), 5 is # (passage), 6 is space, 7 is stairs

      if (input=="-")
      {
        wallFloor[y][x]=1;
      }
      else if (input=="|")
      {
        wallFloor[y][x]=2;
      }
      else if (input==".")
      {
        wallFloor[y][x]=3;
      }
      else if (input=="+")
      {
        wallFloor[y][x]=4;
      }
      else if (input=="#")
      {
        wallFloor[y][x]=5;
      }
      else if (input==" ")
      {
        wallFloor[y][x]=6;
      }
      else if (input == "\\")
      {
        wallFloor[y][x]=7;
      }
      else
      {
        wallFloor[y][x]=3;
        if (input=="@")
        {
          curPlayer.setLocation(y,x);
        }
        else if (input=="H")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]= new Human(y,x);
        }
        else if (input=="W")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]= new Dwarf(y,x);
        }
        else if (input=="E")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]= new Elf(y,x);
        }
        else if (input=="O")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]= new Orc(y,x);
        }
        else if (input=="M")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]= new Merchant(y,x);
        }
        else if (input=="D")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]=Dragon(y,x,NULL);

        }
        else if (input=="L")
        {
          enemyThereFloor[y][x]=true;
          enemyFloor[y][x]= new Halfling(y,x);
        }//end of reading in enemy cases

        else if (input==0)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Potion(y,x,"Potion","RH");
        }
        else if (input==1)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Potion(y,x,"Potion","BA");
        }
        else if (input==2)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Potion(y,x,"Potion","BD");
        }
        else if (input==3)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Potion(y,x,"Potion","PH");
        }
        else if (input==4)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Potion(y,x,"Potion","WA");
        }
        else if (input==5)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Potion(y,x,"Potion","WD");
        }//end of reading in potions cases

        else if (input==6)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Treasure(y,x,"Treasre","small");
        }
        else if (input==7)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Treasure(y,x,"Treasre","normal");
        }
        else if (input==8)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Treasure(y,x,"Treasre","merchant");
        }
        else if (input==9)
        {
          itemThereFloor[y][x]=true;
          itemFLoor[y][x]=new Treasure(y,x,"Treasure","dragon");
        }
      }//end of non-wall cases
    }//end of one row of input
  }//end of reading in input
  for (int y=0;y<25;y++) //linking dragons with their hoards
  {
    for (int x=0;x<79;x++)
    {
      if (enemyThereFloor[y][x])
      {
        Enemy searchingDragon=enemyFloor[y][x];
        if (searchingDragon.getType()=="Dragon")
        {
          Treasure* foundHoard=lookForHoard(searchingDragon.getLocationY,searchingDragon.getLocationX)
          searchingDragon.hoard=foundHoard;
        }
      }
    }
  }
}

Treasure* Floor::lookForHoard(int row,int col)
{
  for (int y=row-1; y<=row+1; y++)
  {
    for (int x=col-1; x<=col+1; x++)
    {
      if (itemThereFloor.[y][x]&&(itemFLoor[y][x]).getName=="dragon")
      {
        return &(itemFLoor[y][x]);
      }
    }
  }
}
return NULL;


Enemy* Floor::lookForEnemy(int row,int col)
{
  for (int y=row-1; y<=row+1; y++)
  {
    for (int x=col-1; x<=col+1; x++)
    {
      if (enemyThereFloor.[y][x])

      return &enemyFloor[y][x];
    }
  }
}
return NULL;
}

Potion* Floor::lookForPotion(int row,int col)
{
  for (int y=row-1; y<=row+1; y++)
  {
    for (int x=col-1; x<=col+1; x++)
    {
      if (itemThereFloor.[y][x])
      {
        if (itemFloor[y][x].getType()=="Potion")
        {
          return &itemFloor[y][x];
        }
      }
    }
  }
  return NULL;
}


int Floor::getWallAt(int row,int col)
{
  return wallFloor[row][col];
}

bool Floor::isItemAt(int row,int col)
{
  return itemThereFloor[row][col];
}

Item Floor::getItemAt(int row,int col)
{
  return itemFloor[row][col];
}

bool Floor::isEnemyAt(int row,int col)
{
  return enemyThereFloor[row][col];
}

Enemy Floor::getEnemyAt(int row,int col)
{
  return enemyFloor[row][col];
}

void removeItem(int row,int col)
{
  itemThereFloor[row][col]=false;
}

void removeEnemy(int row,int col)
{
  enemyThereFloor[row][col]=false;
}

void placeDragon(Treasure* hoard)
{
  int row = hoard.getRow();
  int col = hoard.getCol();
  for (int y=-1; y<=1; y++)
  {
    for (int x=-1; x<=1; x++)
    {
      if (!itemThereFloor[row+y][col+x]&&!enemyThereFloor[row+y][col+x])
      {
        generateDragon(row+y,col+x,hoard);
        break;
      }
    }
  }
}
void floorAfterTurn()
{
  int col=79;
  int row=25;

  for (int y=0; y<row; y++)
  {
    for (int x=0; x<col; x++)
    {
      if (y=curPlayer.row&&x=curPlayer.col) //check for player at (x,y)
      {
        cout << "@";
      }
      else if (isItemAt(y,x)) //check for item at (x,y)
      {
        Item item=getItemAt(y,x);
        string type=item.getType();
        if (type=="treasure")
        {
          cout << "G";
        }
        else if (type="potion")
        {
          cout << "P";
        }
      }//end of item display
      else if (isEnemyAt(y,x)) //check for enemy at (x,y);
      {
        Enemy enemy=getEnemyAt(y,x);
        string type=enemy.getType();
        // displays the correct symbol depending on the type of enemy;
        if (type=="human")
        {
          cout << "H";
        }
        else if (type=="dwarf")
        {
          cout << "W";
        }
        else if (type=="elf")
        {
          cout << "E";
        }
        else if (type=="orc")
        {
          cout << "O";
        }
        else if (type=="merchant")
        {
          cout << "M";
        }
        else if (type=="dragon")
        {
          cout << "D";
        }
        else if (type=="halfling")
        {
          cout << "L";
        }
        //end of enemy type displays
      }//end of enemy display

      else //display of walls/doors/space
      {
        int type=getWallAt(y,x);

        if (type==1)
        {
          cout << "|";
        }
        else if (type==2)
        {
          cout << "-";
        }
        else if (type==3)
        {
          cout << "."; //floor
        }
        else if (type==4)
        {
          cout << "+"; //door
        }
        else if (type==5)
        {
          cout << "#"; //passage between chambers
        }
        else if (type==6)
        {
          cout << " "; //space outside of the chambers, impassable
        }
      }//end of wall display
    }//end of one row
    cout << endl;
  }//end of floor display
}//end of floor display function

void enemyMovePhase()
{
  for(int y=0; y<25; y++)
  {
    for (int x=0; x<79;x++)
    {
      if (enemyThereFloor[y][x])
      {
        Enemy currentEnemy=enemyFloor[y][x];
        if(!currentEnemy.hasMoved)
        {
          currentEnemy.move()
        }
      }
    }
  }
}

void startTurn()//refreshes the action availability of player and enemies
{
  curPlayer.refreshTurn();
  for(int y=0; y<25; y++)
  {
    for (int x=0; x<79;x++)
    {
      if (enemyThereFloor[y][x])
      {
        enemyFloor[y][x].refreshTurn();
      }
    }
  }
}
