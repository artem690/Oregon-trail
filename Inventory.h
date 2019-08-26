using namespace std;

#ifndef Inventory_H
#define Inventory_H

class Inventory

{
    
    public:
        
        Inventory();
        void setOxen(int);
        void setFood(int);
        void setBullets(int);
        void setWagonParts(int);
        void setMedKit(int);
        void setCash(double);
        double getCash();
        int getOxen();
        int getFood();
        int getBullets();
        int getWagonParts();
        int getMedKit();
        
        
    private:
    
        int totalOxen;
        int totalYoke;
        int totalFood;
        int totalBullets;
        int totalWagonParts;
        int totalMedKit;
        double cash;
    
};

#endif