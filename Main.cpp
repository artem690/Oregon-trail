#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <ctime>

#include "GameDriver.h"
#include "Store.h"
#include "Player.h"
#include "Inventory.h"
#include "Date.h"

using namespace std;

int main()
{
    srand(time(NULL)); // true random
    
    Store s;
    Player p;
    Inventory i;
    GameDriver game;
    Date d;
    
    game.readFiles();
    game.names();
    game.firstPurchase();
    s.shopMenu(i);
    d.userPicksDate();
    game.takingTurns(i, d, p);
   	return 0;
}
   	
    
