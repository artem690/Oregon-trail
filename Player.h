#include <string>
using namespace std;

#ifndef Player_H
#define Player_H

class Player
{
    
    public:
        
        Player(); 
        Player(string);
        void setPlayer(string);
        string getPlayer();
        void dying();
        bool getDying();
        
    private:
    
        string name;
        double cash;
        bool died = false;
};

#endif