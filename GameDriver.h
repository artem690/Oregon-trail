#include "Inventory.h"
#include "Player.h"
#include "Date.h"
#include "Store.h"

using namespace std;

#ifndef GameDriver_H
#define GameDriver_H

class GameDriver
{
    public:
    
        GameDriver();
        
        void names();
        double firstPurchase();
        void shopMenu();
        int takingTurns(Inventory &,Date, Player);
        void setMilesTraveled(int);
        int getMilesTraveled();
        void readFiles();
        void misfortunes(Inventory &);
        void ridersAttacks(Inventory &);
        void milestones(Inventory &, Store &);
        int printResults(Inventory &, Date &);
         

    private:
       

        Date d;
        int totalMiles;
        Store s;
        int numPlayers = 5;
        Player players[5];
        string mstones[11][3];// full, sorted array of milestones (rivers and forts sorted by ascending distance from start)
        int msPassedCount;
};

#endif