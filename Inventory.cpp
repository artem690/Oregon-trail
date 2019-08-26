#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "Store.h"
#include "Inventory.h"

using namespace std;

Inventory::Inventory() // default constructor
{
   totalOxen = 0.0;
   totalFood = 0.0;
   totalBullets = 0.0;
   totalWagonParts = 0.0;
   totalMedKit = 0.0;
   cash = 1000.00;
}
// all this function getting and setting all iteams 
void Inventory::setCash(double money)
{
    cash = cash + money;
}
double Inventory::getCash()
{
    return cash;
}

void Inventory::setOxen(int addedOxen)
{
    totalOxen = totalOxen + addedOxen;
}
int Inventory::getOxen()
{
    return totalOxen;
}

// more sets and gets too keep truck of iteams i have 


void Inventory::setFood(int addedFood)
{
    totalFood = totalFood + addedFood;
}
int Inventory::getFood()
{
    return totalFood;
}

void Inventory::setBullets(int addedBullets)
{
    totalBullets += addedBullets;
}
int Inventory::getBullets()
{
    return totalBullets;
}


void Inventory::setWagonParts(int addedWagonParts)
{
    totalWagonParts = totalWagonParts + addedWagonParts;
}
int Inventory::getWagonParts()
{
    return totalWagonParts;
}
void Inventory::setMedKit(int addedMedKit)
{
    totalMedKit = totalMedKit + addedMedKit;
}
int Inventory::getMedKit()
{
    return totalMedKit;
}
