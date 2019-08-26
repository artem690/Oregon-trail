#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "Player.h"

using namespace std;

Player::Player() // default constructor 
{
    name = "";
    //died = false;
}

Player::Player(string name2) // players names
{
    name = name2;
}

void Player::setPlayer(string names) // setting players names
{
   name = names;
}

string Player::getPlayer() // getting names
{
    return name;
}


void Player::dying() // for dying players
{
     died = true;
}

bool Player::getDying() // return
{
    return died;
}
