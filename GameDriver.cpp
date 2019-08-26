#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <cmath>
#include <ctime>


#include "Store.h"
#include "Player.h"
#include "GameDriver.h"
#include "Inventory.h"
#include "Date.h"

using namespace std;

Player p;
GameDriver::GameDriver() // default constructor 
{
    totalMiles = 0;
    msPassedCount = 0;
    
}
void GameDriver::setMilesTraveled(int addedMiles) // setting milege by adding 
{
    totalMiles = totalMiles + addedMiles;
}
int GameDriver::getMilesTraveled() // getting milege 
{
    return totalMiles;
}

void GameDriver::names() // function saying welcome to the game and take all names and printing rules 
{
    // variable 
    int numItems;
    int totalPrice;
    cout << endl;
    cout << "==========WELCOME TO THE OREGON TRAIL==========" << endl;
    cout << endl;
    cout << "THIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM INDEPENDENCE, MISSOURI" << endl;
    cout << "TO OREGON CITY, OREGON IN 1847. YOUR FAMILY OFFIVE WILL COVER" << endl;
    cout << "THE 2040 MILE OREGON TRAIL IN 5-6 MONTHS --- IF YOU MAKE IT ALIVE." << endl;
    cout << endl;
    
	cout << "What is the name of the leader of the wagon?" << endl;
	string name;
    getline(cin, name);
    cout << endl;
	players[0].setPlayer(name); // setting leader
    cout << "What are the name of the four other member in your party?" << endl;
	for (int i = 1; i < 5; ++i) // setting the rest of the group names
	{
		cout  << i << ". ";
		getline(cin, name);
		players[i].setPlayer(name);
	}
	
	cout << endl;
	ifstream file;
	 // reading from the file rules and printing them out
    file.open("store_info.txt");
    // variables
    string text;
    string line = "";
    if (file.is_open())
    {
    	while (getline(file, line)) // loop to go to each line
        {
            text = line;
            cout << text << endl;
        }
    }
}

double GameDriver::firstPurchase() // just to display that wagon was purchased 
{
	Store buy;
	buy.display();
}

int GameDriver::printResults(Inventory &i, Date &d) // saving into a file results of the game
{
    ofstream filee("results.txt"); // printing to the file
    filee << "=====Status Update=====" << endl;
    filee << "○ Current date: " << d.getStartMonth() << "/" << d.getStartDay() << "/1847" << endl;
    filee << "○ Miles traveled: " << getMilesTraveled() << endl;
    filee << "○ Distance until the next milestone: " << (stoi(mstones[msPassedCount][1]) - getMilesTraveled()) << "mi" << endl;
    filee << "○ Food available: " << i.getFood() << " lbs"<< endl;
    filee << "○ Number of Bullets available: " << i.getBullets() << endl;
    filee << "○ Cash available: $" << i.getCash() << endl;
    exit(0); // basically return 0
    
}

int GameDriver::takingTurns(Inventory &i, Date d, Player p) // this function is taking care of turns and status update (rest / hunt / etc) 
{
    // declairing all variables
    int choice;
    int daysTraveled = 0;
    int restedDays = 0;
    int distanceTraveled = 0;
    int totalMiles = 0;
    int foodLeft= 0;
    
    int probability = 0;
    string pick;
    string temp;
   	while (choice != 4) 
    {
        cout << endl; 
        cout << "=====Status Update=====" << endl;
        cout << "○ Current date: " << d.getStartMonth() << "/" << d.getStartDay() << "/1847" << endl;
        cout << "○ Miles traveled: " << getMilesTraveled() << endl;
        cout << "○ Distance until the next milestone: " << (stoi(mstones[msPassedCount][1]) - getMilesTraveled()) << "mi" << endl;
        cout << "○ Food available: " << i.getFood() << " lbs"<< endl;
        cout << "○ Number of Bullets available: " << i.getBullets() << endl;
        cout << "○ Cash available: $" << i.getCash() << endl;
        
        cout << endl;
     
        cout << "You have 3 options:" << endl;
        cout << "1. Rest" << endl;
        cout << "2. Continue traveling" << endl;
        cout << "3. Hunt" << endl;
        cout << "4. Quit game" << endl;
        cout << "Please make a choice: ";
        // more variables
        int food2 = 0;
        int extraFood = 0;       
        bool meetAnimal;
        getline(cin, temp);
        choice = stoi(temp);
        int food = 0;
        int numBullets = 0;
        int answer;
        
        switch (choice) // switch cases for 3 options when turns presented 
        {
            case 1:
                // resting
                cout << endl;
                cout << "You chose to rest" << endl;
                restedDays = (rand() % 3) + 1;  // random for resting between 1 and 3 days 
                d.addDates(restedDays); // add rested days to updete date
                cout << "You had " << restedDays << " days for rest" << endl;
                food = -(restedDays * 3 * numPlayers); // setting food after rested days
                i.setFood(food);
                cout << "You have " << i.getFood() << " lbs of food left after resting for " << restedDays << " days"<< endl;
                if (i.getFood() <= 0) // edge case if out of food 
                {
                    cout << endl;
                    cout << "You have no food left! Game over!" << endl;
                    printResults(i, d); // function that ends the game
                }
                misfortunes(i); // calling function 
                ridersAttacks(i); // calling function
                
            break;
                
            case 2:
                // traveling
                cout << endl;
                cout << "You chose to continue on the trail" <<endl;
                distanceTraveled = (rand() % 71) + 70; // random for traveling for miles in between 70 and 140
                cout << "You have traveled " << distanceTraveled << " miles" << endl;
                cout << "The travel turn was 2 week" << endl;
                d.addDates(14); // add to date to update the date 
                setMilesTraveled(distanceTraveled); // setting milege 
                food = -(14 * 3 * numPlayers); // setting food 
                i.setFood(food);
                cout <<"You have " << i.getFood() << " lbs of food left after traveling" << endl; 
                if (i.getFood() <= 0) // out of food
                {
                    cout << endl;
                    cout << "You have no food left! Game over!" << endl;
                    printResults(i, d);
                }
                if (getMilesTraveled() >= 2040) // when arrive at oregon 
                {
                    cout << endl;
                    cout << "YOU HAVE ARRIVED TO OREGON! CONGRATS! YOU WON THE GAME!" << endl;
                    printResults(i, d); // calling function end game
                }
                if (d.getStartMonth() >= 11) // if did not arrive to oregon before November 30th
                {
                    cout << "You did not get in Oregon in time. Game over!";
                    printResults(i,d); // end game
                }
                // calling all functions 
                misfortunes(i);
                ridersAttacks(i);
                milestones(i,s); // checks milestones after each travel
                
            break;
            
            case 3:
                // hunting 
                probability = (rand() % 100) + 1; // random betweeen 1 and 100 
                cout << endl;
                cout << "You chose to hunt" << endl;
                cout << endl;
                d.addDates(1);// add 1 day to date
                meetAnimal = false; // bool to help with hunting process 
                // COMMENTING ONLY FOR ONE ANIMAL. THE REST OF THE ANIMALS WORK THE SAME EXACT WAY
                if (probability <= 50) // RABBIT 50
                {
                    meetAnimal = true; 
                    cout << "You got lucky! You encountered a rabbit! Do you want to hunt: (1) is yes, (2) is no" << endl;
                    getline(cin, pick);
                    if (stoi(pick) == 1)
                    {
                        if (i.getBullets() < 10) // if out of bullets
                        {
                            cout << "You cannot hunt, you do not have enough bullets" << endl;
                        }
                        else
                        {
                            cout << "You going to hunt a rabbit" << endl;
                            cout << "You have to solve a puzzle in order to hunt" << endl;
                            cout << "Please pick a number in between 1 and 10. You have 3 tries" << endl;
                            int puzzle = (rand() % 10) + 1; // thats a puzzle that needs to be solved 
                            int number;
                            int numTries = 0;
                            getline(cin, temp);
                            number = stoi(temp);
                            int flag = false; // bool to help hunting process
                            while (numTries <= 1 && flag == false) // if number of tries for puzzle 3 and false flag
                            {
                                if (number == puzzle) // when solve puzzle 
                                {
                                    cout << "Your hunting was successful. You caught a rabbit!" << endl;
                                    flag = true; // turn flag to true means guessed the puzzle and no need to enter a number again
                                    i.setFood(2); // add food
                                    i.setBullets(-10); // substruct bullets 
                                    cout << "You spent 10 bullets to hunt a rabbit. You have " << i.getBullets() << " bullets left" << endl;
                                    cout << "You gained 2 lbs. of food" << endl;
                                    cout << "Now you have " << i.getFood() << " lbs. of food after hunting a rabbit" << endl;
                                }
                                else 
                                {
                                    // 3 tries if do not guess the puzzle. keeps bringing it here 
                                    cout << "Try again" << endl;
                                    numTries++; // number of tries goes up
                                    cout << "Enter another number: ";
                                    getline(cin, temp);
                                    number = stoi(temp);
                                    
                                    if(numTries == 2) // if do not want to hunt 
                                    {
                                        cout << "Sorry, you were not able to hunt a rabbit" << endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                    else if (stoi(pick) == 2)
                    {
                        cout << "You chose not to hunt a rabbit" << endl;
                    }
                    
                }
                probability = (rand() % 100) + 1;
                if (probability <= 25) //FOX 25
                {
                    meetAnimal = true;
                    cout << "You got lucky! You encountered a fox! Do you want to hunt: (1) is yes, (2) is no" << endl;
                    getline(cin, pick);
                    if (stoi(pick) == 1)
                    {
                        if (i.getBullets() < 10)
                        {
                            cout << "You cannot hunt, you do not have enough bullets" << endl;
                        }
                        else
                        {
                            cout << "You going to hunt a fox" << endl;
                            cout << "You have to solve a puzzle in order to hunt" << endl;
                            cout << "Please pick a number in between 1 and 10. You have 3 tries" << endl;
                            int puzzle = (rand() % 10) + 1;
                            int number;
                            int numTries = 0;
                            getline(cin, temp);
                            number = stoi(temp);
                            int flag = false;
                            while (numTries <= 1 && flag == false) //(flag == false) // not good change // starts at 0?
                            {
                                if (number == puzzle)
                                {
                                    cout << "Your hunting was successful. You caught a fox!" << endl;
                                    flag = true;
                                    i.setFood(5);
                                    i.setBullets(-8);
                                    cout << "You spent 8 bullets to hunt a fox. You have " << i.getBullets() << " bullets left" << endl;
                                    cout << "You gained 5 lbs. of food" << endl;
                                    cout << "Now you have " << i.getFood() << " lbs. of food after hunting a fox" << endl;
                                }
                                else 
                                {
                                    
                                    cout << "Try again" << endl;
                                    numTries++;
                                    cout << "Enter another number: ";
                                    getline(cin, temp);
                                    number = stoi(temp);
                                    
                                    if(numTries == 2)
                                    {
                                        cout << "Sorry, you were not able to hunt a fox" << endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                    else if (stoi(pick) == 2)
                    {
                        cout << "You chose not to hunt a fox" << endl;
                    }
                    
                }
                probability = (rand() % 100) + 1;
                if (probability <= 15) // DEER 15
                {
                    meetAnimal = true;
                    cout << "You got lucky! You encountered a deer! Do you want to hunt: (1) is yes, (2) is no" << endl;
                    getline(cin, pick);
                    if (stoi(pick) == 1)
                    {
                        if (i.getBullets() < 10)
                        {
                            cout << "You cannot hunt, you do not have enough bullets" << endl;
                        }
                        else
                        {
                            cout << "You going to hunt a deer" << endl;
                            cout << "You have to solve a puzzle in order to hunt" << endl;
                            cout << "Please pick a number in between 1 and 10. You have 3 tries" << endl;
                            int puzzle = (rand() % 10) + 1;
                            int number;
                            int numTries = 0;
                            getline(cin, temp);
                            number = stoi(temp);
                            int flag = false;
                            while (numTries <= 1 && flag == false) //(flag == false) // not good change // starts at 0?
                            {
                                if (number == puzzle)
                                {
                                    cout << "Your hunting was successful. You caught a deer!" << endl;
                                    flag = true;
                                    food = (rand() % 26) + 30;
                                    i.setFood(food);
                                    i.setBullets(-5);
                                    cout << "You spent 5 bullets to hunt a deer. You have " << i.getBullets() << " bullets left" << endl;
                                    cout << "You gained " << food << " lbs. of food" << endl;
                                    cout << "Now you have " << i.getFood() << " lbs. of food after hunting a deer" << endl;
                                }
                                else 
                                {
                                    
                                    cout << "Try again" << endl;
                                    numTries++;
                                    cout << "Enter another number: ";
                                    getline(cin, temp);
                                    number = stoi(temp);
                                    
                                    if(numTries == 2)
                                    {
                                        cout << "Sorry, you were not able to hunt a deer" << endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                    else if (stoi(pick) == 2)
                    {
                        cout << "You chose not to hunt a deer" << endl;
                    }
                    
                }
                probability = (rand() % 100) + 1;
                if (probability <= 7) // BEAR 7
                {
                    meetAnimal = true;
                    cout << "You got lucky! You encountered a bear! Do you want to hunt: (1) is yes, (2) is no" << endl;
                    getline(cin, pick);
                    if (stoi(pick) == 1)
                    {
                        if (i.getBullets() < 10)
                        {
                            cout << "You cannot hunt, you do not have enough bullets" << endl;
                        }
                        else
                        {
                            cout << "You going to hunt a bear" << endl;
                            cout << "You have to solve a puzzle in order to hunt" << endl;
                            cout << "Please pick a number in between 1 and 10. You have 3 tries" << endl;
                            int puzzle = (rand() % 10) + 1;
                            int number;
                            int numTries = 0;
                            getline(cin, temp);
                            number = stoi(temp);
                            int flag = false;
                            while (numTries <= 1 && flag == false) //(flag == false) // not good change // starts at 0?
                            {
                                if (number == puzzle)
                                {
                                    cout << "Your hunting was successful. You caught a bear!" << endl;
                                    flag = true;
                                    food = (rand() % 251) + 100;
                                    i.setFood(food);
                                    i.setBullets(-10);
                                    cout << "You spent 10 bullets to hunt a bear. You have " << i.getBullets() << " bullets left" << endl;
                                    cout << "You gained " << food << " lbs. of food" << endl;
                                    cout << "Now you have " << i.getFood() << " lbs. of food after hunting a bear" << endl;
                                }
                                else 
                                {
                                    
                                    cout << "Try again" << endl;
                                    numTries++;
                                    cout << "Enter another number: ";
                                    getline(cin, temp);
                                    number = stoi(temp);
                                    
                                    if(numTries == 2)
                                    {
                                        cout << "Sorry, you were not able to hunt a bear" << endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                    else if (stoi(pick) == 2)
                    {
                        cout << "You chose not to hunt a bear" << endl;
                    }
                    
                }
                probability = (rand() % 100) + 1;
                if (probability <= 5) // MOOSE 5
                {
                    meetAnimal = true;
                    cout << "You got lucky! You encountered a moose! Do you want to hunt: (1) is yes, (2) is no" << endl;
                    getline(cin, pick);
                    if (stoi(pick) == 1)
                    {
                        if (i.getBullets() < 10)
                        {
                            cout << "You cannot hunt, you do not have enough bullets" << endl;
                        }
                        else
                        {
                            cout << "You going to hunt a moose" << endl;
                            cout << "You have to solve a puzzle in order to hunt" << endl;
                            cout << "Please pick a number in between 1 and 10. You have 3 tries" << endl;
                            int puzzle = (rand() % 10) + 1;
                            int number;
                            int numTries = 0;
                            getline(cin, temp);
                            number = stoi(temp);
                            int flag = false;
                            while (numTries <= 1 && flag == false) //(flag == false) // not good change // starts at 0?
                            {
                                if (number == puzzle)
                                {
                                    cout << "Your hunting was successful. You caught a moose!" << endl;
                                    flag = true;
                                    food = (rand() % 301) + 300;
                                    i.setFood(food);
                                    i.setBullets(-12);
                                    cout << "You spent 12 bullets to hunt a moose. You have " << i.getBullets() << " bullets left" << endl;
                                    cout << "You gained " << food << " lbs. of food" << endl;
                                    cout << "Now you have " << i.getFood() << " lbs. of food after hunting a moose" << endl;
                                }
                                else 
                                {
                                    
                                    cout << "Try again" << endl;
                                    numTries++;
                                    cout << "Enter another number: ";
                                    getline(cin, temp);
                                    number = stoi(temp);
                                    
                                    if(numTries == 2)
                                    {
                                        cout << "Sorry, you were not able to hunt a moose" << endl;
                                    }
                                    
                                }
                            }
                        }
                    }
                    else if (stoi(pick) == 2)
                    {
                        cout << "You chose not to hunt a moose" << endl;
                    }
                    
                }
                
                if (meetAnimal == false)
                {
                    cout << "Sorry you did not encountered any animals" << endl;
                }
                if (i.getFood() >= 1000) // wagon cannot have more than 1000 lbs 
                {
                    cout << endl;
                    cout << "Now you have more than 1000 lbs of food" << endl;
                    cout << "Wagon cannot hold more than 1000 lbs of food" << endl;
                    cout << "You need to leave some food" << endl;
                    food2 = i.getFood();
                    extraFood = food2 - 1000; // taking out extra food setting it to max which is 1000
                    i.setFood(-extraFood);
                    cout << "You have " << i.getFood() << " lbs of food now" << endl;
                }
                cout << endl; // how well people want to eat after hunting day
                cout << "How well do your people want to eat?" << endl;
                cout << "1. Poorly: 2 lbs of food, per person" << endl;
                cout << "2. Moderately: 3 lbs of food, per person" << endl;
                cout << "3. Well: 5 lbs of food, per person" << endl;
                cout << "Please make a choice:";
                getline(cin, temp);
                answer = stoi(temp);
                if (answer == 1)
                {
                    food = ((2 * numPlayers));
                    i.setFood(-food); // setting food after eating
                    i.getFood();
                    cout << "Your party have eaten " << food << " lbs of food" << endl;
                }
                else if (answer == 2)
                {
                    food = ((3 * numPlayers));
                    i.setFood(-food);// setting food after eating
                    i.getFood();
                    cout << "Your party have eaten " << food << " lbs of food" << endl;
                }
                else if (answer == 3)
                {
                    food = ((5 * numPlayers));
                    i.setFood(-food);// setting food after eating
                    i.getFood();
                    cout << "Your party have eaten " << food << " lbs of food" << endl;
                }
                if (i.getFood() <= 0) // no food game over
                {
                    cout << "You have no food left! Game over" << endl;
                    printResults(i, d); // ending game/ results 
                }
                misfortunes(i); // calling functions 
                ridersAttacks(i); // caling functions 
            break;
            
            case 4:
                cout << "You chose to quit the game! Bye." << endl;
            
            default:
                cout << "Invalid choice. Please select again" << endl; // invalid choice 
          
        }
    }
}
void GameDriver::misfortunes(Inventory &i) // misfortunes function takes care of all misfortunes 
{
    int prob = (rand() % 100) + 1; // probability for a misfortune to happen 
    string temp;
    if (prob <= 40) // 40%
    {
        cout << endl;
        cout << "Misfortune happened!" << endl;
        int randomPlayer = rand() % numPlayers; // picking a random playr to whome misfortune happens 
        while(players[randomPlayer].getDying()) // accounting for people that die so does not pick dead person 
        {
            randomPlayer = rand() % numPlayers;// random 
        }
        int random = (rand() % 3) + 1; // picking randomly which misfortune happens there are 3 total
        if (random == 1)
        {
            int random2 = (rand() % 6) + 1; // 6 different diseases. picking randomly 
            // COMMENTING FOR ONE SICKNESS. THERE REST WORK EXACTLY THE SAME
            if (random2 == 1 )
            {
                cout << "Oh NO! " << players[randomPlayer].getPlayer() << " has typhoid!" << endl; // random player gets sick
                if (i.getMedKit() >= 1) // if there are med kits
                {
                    cout << players[randomPlayer].getPlayer() << " used medical kit" << endl;
                    i.setMedKit(-1); // substructing med kit 
                    int chancesDying = (rand() % 100) + 1; // chances of dying random 
                    if (chancesDying <= 50) // 50% 
                    {
                        cout << players[randomPlayer].getPlayer() << " did not survive and died" << endl;
                        players[randomPlayer].dying(); // function that accounts for dead people. basically killing a person
                        numPlayers--; // dicreasing number of players
                        if (randomPlayer == 0) // if leader dies which is at possition 0 in the array
                        {
                            cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                            printResults(i, d); // end game/printing results
                        }
                    }
                    else
                        cout << players[randomPlayer].getPlayer() << " survived typhoid" << endl;
                    
                    cout << "You have " << i.getMedKit() << " medical kits left" << endl;
                }
                else if (i.getMedKit() < 1 ) // if there are no med kits
                {
                    int choice;
                    int food = 0;
                    cout << "You do not have any medical kits" << endl;
                    cout <<"You can rest (1) or continue on the trail (2)" << endl; // two options given to the player
                    cout << "Please make a choice:";
                    
                    getline(cin, temp); 
                    choice = stoi(temp);
                    
                    if (choice == 1)
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1; // random for chances of dying 
                        cout << "You chose to REST FOR 3 DAYS" << endl;
                        if (chancesDying <= 30) // 30%
                        {
                            cout << players[randomPlayer].getPlayer() << " still died" << endl;
                            players[randomPlayer].dying(); // killing a person 
                            numPlayers--; // number of players goes down
                            if (randomPlayer == 0) // if leader dies 
                            {
                                cout << "Leader died. You cannot continue without the leader Game over!" << endl;
                                printResults(i, d); // end game
                            }
                        }
                        else 
                             cout << players[randomPlayer].getPlayer() << " survived typhoid" << endl;
                        d.addDates(3); // add 3 days to date 
                        food = -(3 * 3 * numPlayers); // setting food 
                        i.setFood(food);
                        cout << "You have " << i.getFood() << " lbs of food left after resting for 3 days" << endl;
                    }
                    if (choice == 2 )
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1; // % of dying 
                     
                        cout << "you choose to PRESS ON" << endl;
                        if (chancesDying <= 70) // 70%
                        {
                            cout << players[randomPlayer].getPlayer() << " died" << endl;
                            players[randomPlayer].dying(); // killing a person 
                            numPlayers--; // num players goes down
                            
                            if (randomPlayer == 0) // leaders death 
                            {
                                cout << "Leader died. Game over!" << endl;
                                printResults(i, d); // end game
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived typhoid" << endl;
                        int distanceTraveled = (rand() % 71) + 70; // random in between 70 and 140 for traveling miles 
                        cout << "You have traveled " << distanceTraveled << " miles" << endl;
                        d.addDates(14); // add 14 to date 
                        setMilesTraveled(distanceTraveled);
                        food = -(14 * 3 * numPlayers); // setting food 
                        i.setFood(food);
                        cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    }
                
                }
                 
            }
            else if (random2 == 2)
            {
               cout << "Oh NO! " << players[randomPlayer].getPlayer() << " has cholera!" << endl; 
               if (i.getMedKit() >= 1)
                {
                     cout << players[randomPlayer].getPlayer() << " used medical kit" << endl;
                    i.setMedKit(-1);
                    int chancesDying = (rand() % 100) + 1;
                    if (chancesDying <= 50)
                    {

                        cout << players[randomPlayer].getPlayer() << " did not survive and  died" << endl;
                        players[randomPlayer].dying();
                        numPlayers--;
                        if (randomPlayer == 0)
                        {
                            cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                            printResults(i, d);
                        }
                       // flag == true;
                    }
                    else 
                        cout << players[randomPlayer].getPlayer() << " survived cholera" << endl;
                  
                    cout << "You have " << i.getMedKit() << " medical kits left" << endl;
                }
                else if (i.getMedKit() < 1 )
                {
                    int choice;
                    int food = 0;
                    cout << "You do not have any medical kits" << endl;
                    cout <<"You can rest (1) or continue on the trail (2)" << endl;
                    cout << "Please make a choice:";
                    getline(cin, temp); choice = stoi(temp);
                    if (choice == 1)
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                        cout << "You chose to REST FOR 3 DAYS" << endl;
                        if (chancesDying <= 30)
                        {
                            cout << players[randomPlayer].getPlayer() << " still died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived cholera" << endl;
                        d.addDates(3);
                        food = -(3 * 3 * numPlayers);
                        i.setFood(food);
                        cout << "You have " << i.getFood() << " lbs of food left after resting for " << endl;
                    }
                    if (choice == 2 )
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                     
                        cout << "you choose to PRESS ON" << endl;
                        if (chancesDying <= 70)
                        {
                            cout << players[randomPlayer].getPlayer() << " died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived cholera" << endl;
                        int distanceTraveled = (rand() % 71) + 70;
                        cout << "You have traveled " << distanceTraveled << " miles" << endl;
                        d.addDates(14);
                        setMilesTraveled(distanceTraveled);
                        food = -(14 * 3 * numPlayers);
                        i.setFood(food);
                        cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    }
                
                }
            }
            else if (random2 == 3)
            {
                cout << "Oh NO! " << players[randomPlayer].getPlayer() << " has diarrhea!" << endl;
                if (i.getMedKit() >= 1)
                {
                     cout << players[randomPlayer].getPlayer() << " used medical kit" << endl;
                    i.setMedKit(-1);
                    int chancesDying = (rand() % 100) + 1;
                    if (chancesDying <= 50)
                    {

                        cout << players[randomPlayer].getPlayer() << " did not survive and died" << endl;
                        players[randomPlayer].dying();
                        numPlayers--;
                        if (randomPlayer == 0)
                        {
                            cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                            printResults(i, d);
                        }
                    }
                    else 
                        cout << players[randomPlayer].getPlayer() << " survived diarrhea" << endl;
                   
                    cout << "You have " << i.getMedKit() << " medical kits left" << endl;
                }
                else if (i.getMedKit() < 1 )
                {
                    int choice;
                    int food = 0;
                    cout << "You do not have any medical kits" << endl;
                    cout <<"You can rest (1) or continue on the trail (2)" << endl;
                    cout << "Please make a choice:";
                    getline(cin, temp); choice = stoi(temp);
                    if (choice == 1)
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                        cout << "You chose to REST FOR 3 DAYS" << endl;
                        if (chancesDying <= 30)
                        {
                            cout << players[randomPlayer].getPlayer() << " still died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived diarrhea" << endl;
                        d.addDates(3);
                        food = -(3 * 3 * numPlayers);
                        i.setFood(food);
                        cout << "You have " << i.getFood() << " lbs of food left after resting for " << endl;
                    }
                    if (choice == 2 )
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                     
                        cout << "you choose to PRESS ON" << endl;
                        if (chancesDying <= 70)
                        {
                            cout << players[randomPlayer].getPlayer() << " died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived diarrhea" << endl;
                        int distanceTraveled = (rand() % 71) + 70;
                        cout << "You have traveled " << distanceTraveled << " miles" << endl;
                        d.addDates(14);
                        setMilesTraveled(distanceTraveled);
                        food = -(14 * 3 * numPlayers);
                        i.setFood(food);
                        cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    }
                
                }
            }
            else if (random2 == 4)
            {
                cout << "Oh NO! " << players[randomPlayer].getPlayer() << " has measles!" << endl;
                if (i.getMedKit() >= 1)
                {
                     cout << players[randomPlayer].getPlayer() << " used medical kit" << endl;
                    i.setMedKit(-1);
                    int chancesDying = (rand() % 100) + 1;
                    if (chancesDying <= 50)
                    {

                        cout << players[randomPlayer].getPlayer() << " did not survive and died" << endl;
                        players[randomPlayer].dying();
                        numPlayers--;
                        if (randomPlayer == 0)
                        {
                            cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                            printResults(i, d);
                        }
                    }
                    else 
                        cout << players[randomPlayer].getPlayer() << " survived measles" << endl;
                   
                    cout << "You have " << i.getMedKit() << " medical kits left" << endl;
                }
                else if (i.getMedKit() < 1 )
                {
                   // takingTurns(i,d,p);
                    int choice;
                    int food = 0;
                    cout << "You do not have any medical kits" << endl;
                    cout <<"You can rest (1) or continue on the trail (2)" << endl;
                    cout << "Please make a choice:";
                    getline(cin, temp); choice = stoi(temp);
                    if (choice == 1)
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                        cout << "You chose to REST FOR 3 DAYS" << endl;
                        if (chancesDying <= 30)
                        {
                            cout << players[randomPlayer].getPlayer() << " still died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived diarrhea" << endl;
                        d.addDates(3);
                        food = -(3 * 3 * numPlayers);
                        i.setFood(food);
                        cout << "You have " << i.getFood() << " lbs of food left after resting for " << endl;
                    }
                    if (choice == 2 )
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                     
                        cout << "you choose to PRESS ON" << endl;
                        if (chancesDying <= 70)
                        {
                            cout << players[randomPlayer].getPlayer() << " died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived diarrhea" << endl;
                        int distanceTraveled = (rand() % 71) + 70;
                        cout << "You have traveled " << distanceTraveled << " miles" << endl;
                        d.addDates(14);
                        setMilesTraveled(distanceTraveled);
                        food = -(14 * 3 * numPlayers);
                        i.setFood(food);
                        cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    }
                
                }
            }
            else if (random2 == 5)
            {
                cout << "Oh NO! " << players[randomPlayer].getPlayer() << " has dysentery!" << endl;
                if (i.getMedKit() >= 1)
                {
                     cout << players[randomPlayer].getPlayer() << " used medical kit" << endl;
                    i.setMedKit(-1);
                    int chancesDying = (rand() % 100) + 1;
                    if (chancesDying <= 50)
                    {

                        cout << players[randomPlayer].getPlayer() << " did not survive and died" << endl;
                        players[randomPlayer].dying();
                        numPlayers--;
                        if (randomPlayer == 0)
                        {
                            cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                            printResults(i, d);
                        }
                    }
                    else 
                        cout << players[randomPlayer].getPlayer() << " survived dysentery" << endl;
                  
                    cout << "You have " << i.getMedKit() << " medical kits left" << endl;
                }
                else if (i.getMedKit() < 1 )
                {
                    int choice;
                    int food = 0;
                    cout << "You do not have any medical kits" << endl;
                    cout <<"You can rest (1) or continue on the trail (2)" << endl;
                    cout << "Please make a choice:";
                    getline(cin, temp); choice = stoi(temp);
                    if (choice == 1)
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                        cout << "You chose to REST FOR 3 DAYS" << endl;
                        if (chancesDying <= 30)
                        {
                            cout << players[randomPlayer].getPlayer() << " still died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived dysentery" << endl;
                        d.addDates(3);
                        food = -(3 * 3 * numPlayers);
                        i.setFood(food);
                        cout << "You have " << i.getFood() << " lbs of food left after resting for " << endl;
                    }
                    if (choice == 2 )
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                     
                        cout << "you choose to PRESS ON" << endl;
                        if (chancesDying <= 70)
                        {
                            cout << players[randomPlayer].getPlayer() << " died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived dysentery" << endl;
                        int distanceTraveled = (rand() % 71) + 70;
                        cout << "You have traveled " << distanceTraveled << " miles" << endl;
                        d.addDates(14);
                        setMilesTraveled(distanceTraveled);
                        food = -(14 * 3 * numPlayers);
                        i.setFood(food);
                        cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    }
                
                }
            }
            else if (random2 == 6)
            {
                cout << "Oh NO! " << players[randomPlayer].getPlayer() << " has fever!" << endl;
                if (i.getMedKit() >= 1)
                {
                     cout << players[randomPlayer].getPlayer() << " used medical kit" << endl;
                    i.setMedKit(-1);
                    int chancesDying = (rand() % 100) + 1;
                    if (chancesDying <= 50)
                    {

                        cout << players[randomPlayer].getPlayer() << " did not survive and died" << endl;
                        players[randomPlayer].dying();
                        numPlayers--;
                        
                        if (randomPlayer == 0)
                        {
                            cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                            printResults(i, d);
                        }
                    }
                    else 
                        cout << players[randomPlayer].getPlayer() << " survived fever" << endl;
                    cout << "You have " << i.getMedKit() << " medical kits left" << endl;
                }
                else if (i.getMedKit() < 1 )
                {
                   // takingTurns(i,d,p);
                    int choice;
                    int food = 0;
                    cout << "You do not have any medical kits" << endl;
                    cout <<"You can rest (1) or continue on the trail (2)" << endl;
                    cout << "Please make a choice:";
                    getline(cin, temp); choice = stoi(temp);
                    if (choice == 1)
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                        cout << "You chose to REST FOR 3 DAYS" << endl;
                        if (chancesDying <= 30)
                        {
                            cout << players[randomPlayer].getPlayer() << " still died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived fever" << endl;
                        d.addDates(3);
                        food = -(3 * 3 * numPlayers);
                        i.setFood(food);
                        cout << "You have " << i.getFood() << " lbs of food left after resting for " << endl;
                    }
                    if (choice == 2 )
                    {
                        int chancesDying = 0;
                        chancesDying = (rand() % 100) + 1;
                     
                        cout << "you choose to PRESS ON" << endl;
                        if (chancesDying <= 70)
                        {
                            cout << players[randomPlayer].getPlayer() << " died" << endl;
                            players[randomPlayer].dying();
                            numPlayers--;
                            if (randomPlayer == 0)
                            {
                                cout << "Leader died. You cannot continue without the leader. Game over!" << endl;
                                printResults(i, d);
                            }
                        }
                        else 
                            cout << players[randomPlayer].getPlayer() << " survived fever" << endl;
                        int distanceTraveled = (rand() % 71) + 70;
                        cout << "You have traveled " << distanceTraveled << " miles" << endl;
                        d.addDates(14);
                        setMilesTraveled(distanceTraveled);
                        food = -(14 * 3 * numPlayers);
                        i.setFood(food);
                        cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    }
                
                }
            }
        }
        if (random == 2) // second misfortune oxen dies 
        {
            cout << "Oxen died" << endl;
            i.setOxen(-1); // substruct oxen from inventory
            cout << "You have " << i.getOxen() << " oxens left" << endl;
            if (i.getOxen() <= 0) // adge case if all of them dead
            {
                cout << "All you oxens died. You cannot continue traveling. Game over!" << endl;
                printResults(i, d); // end game 
            }
        }
        if (random == 3) // 3rd misfortune wagon parts break
        {
            cout << "Wagon part broke" << endl;
            i.setWagonParts(-1); // substruction parts from inventory
            cout << "You have " << i.getWagonParts() << " wagon parts left" << endl;
            if (i.getWagonParts() <= 0) // if out of parts
            {
                cout << "All your wagon parts are broken. You cannot continue traveling. Game over!" << endl;
                printResults(i, d); // end game 
            }
        }
        
       
    }
    else 
        1; // does nothing just something to put in else if misfortune does not happen
    
}

void GameDriver::ridersAttacks(Inventory &i) // function that takes care of all rider attacks and choices 
{
    int probab = (((pow(((getMilesTraveled()/100) - 4 ), 2) + 72 ) / (pow(((getMilesTraveled()/100) - 4), 2) + 12) - 1) / 10 ) * 100;// probability of a attack
    int randomNum = (rand() % 100) + 1;  // random number 
    int choice;
    string temp;
    if (probab >= randomNum) // if random number is smaller then probab of attack then attack
    {
        cout << endl;
        cout << "RIDERS AHEAD! THEY LOOK HOSTILE!" << endl;
        cout << "You have 3 options:" << endl;
        cout << "1. Run" << endl;
        cout << "2. Attack" << endl;
        cout << "3. Surrender" << endl; 
        cout << "Please make a choice:";
        getline(cin, temp); 
        choice = stoi(temp);
        double money;
        double moneyLeft;
        if (choice == 1) // running away
        {
            // setting oxens food and parts if they run
            i.setOxen(-1);
            i.setFood(-10);
            i.setWagonParts(-1);
            cout << "You chose to run!" << endl;
            cout << "You lost 1 oxen, 10 lbs of food and 1 wagon part while running away" << endl;
            if (i.getOxen() <= 0)
            {
                cout << "You have no oxens left. Game over!" << endl;
                printResults(i, d); // end game 
            }
            if (i.getFood() <= 0)
            {
                cout << "You have no food left. Game over!" << endl;
                printResults(i, d); // end game 
            }
            if (i.getWagonParts() <= 0)
            {
                cout << "You have no wagon parts left. Game over!" << endl;
                printResults(i, d); // end game 
            }
            
        }
        else if (choice == 2) // attack back
        {
            cout << "You chose to attack riders back" << endl;
            cout << "You have to solve a puzzle in order to have successful attack" << endl;
            cout << "Please pick a number in between 1 and 10. You have 3 tries" << endl;
            int puzzle = (rand() % 10) + 1; // random for puzzle 
            int number;
            int numTries = 0;
            getline(cin, temp);
            number = stoi(temp);
            int flag = false;
            // HERE IS BASICALLY THE SAME AS HUNTING JUST WITH DIFFERET PRINT OUTS 
            while (numTries <= 1 && flag == false) //(flag == false) // not good change // starts at 0?
            {
                if (number == puzzle) // if guess the number for puzzle
                {
                    cout << "Your attack was successful!" << endl;
                    flag = true;
                    i.setFood(50); // settig food 
                    i.setBullets(50); // setting bullets
                    cout << "You have gained 50 bullets. You have " << i.getBullets() << " bullets left" << endl;
                    cout << "You gained 50 lbs. of food. You have " << i.getFood() << " lbs of food now" << endl;
        
                }
                else 
                {
                    // if do not guess the number for puzzles 
                    cout << "Try again" << endl;
                    numTries++;
                    cout << "Enter another number: ";
                    getline(cin, temp);
                    number = stoi(temp);
                    
                    if(numTries == 2) // if did not guess number of puzzle number 
                    {
                        cout << "Sorry, your attack was unsuccessful" << endl;
                        i.setBullets(-50); // substructing bullets 
                        money = i.getCash(); // for substructing cash 
                        moneyLeft = ( money / 100 ) * 25; // to make it 1/4
                        i.setCash(-moneyLeft); // cash
                        cout << "You lost 50 bullets and quarter of your cash. You have " << i.getBullets() << " bullets left" << endl;
                        cout << "You lost quarter of your cash. You have $" << i.getCash() << " left" << endl;
                    }
                    
                }
            }
        }
        else if (choice == 3) // surrender option
        {
            cout << "You chose to surrender!" << endl;
            money = i.getCash();
            moneyLeft = ( money / 100 ) * 25;
            i.setCash(-moneyLeft); // cash that gets taken away
            cout << "Riders took quarter of your cash. You have $" << i.getCash() << " left" << endl;
        }
    }
    
    else 
        1; // does nothing just to have something in else if no attacks happen
    
    
}

void GameDriver::readFiles() // just reading from a file for milestons 
{
    // the way arrays build
    // string forts[6][2] = 
    //         [fortName, distanceFromStart]
        
    // string rivers[4][3] =
    //         [riverName, distanceFromStart, depth]
    ifstream reader("milestones.txt"); // reading from the file 
    string name;
    string fortDist;
    string riverDist;
    string depth;
    int index = 0;
    while(getline(reader, name))
    {
        if(name.length() == 0)  // empty line used for formatting, skipping...
        {
            continue;
        }
        else if(name[0] == 'F')  // if starts with F it means fort so store everything for forts 
        {
            getline(reader, fortDist); // going through the line 
        
            mstones[index][0] = name; // storing name 
            mstones[index][1] = fortDist.substr(0, fortDist.length() - 2); // storing distance - "mi" part
            mstones[index][2] = "0"; // it is for depth setting it to 0
            index++; // index add 1 at time
        }
        else  // else river if does not start with F
        {
            getline(reader, riverDist); // going though the lines 
            getline(reader, depth); // depth
           
            mstones[index][0] = name; // storing names
            mstones[index][1] = riverDist.substr(0, riverDist.length() - 2);  //storing distance - "mi" part
            mstones[index][2] = depth.substr(0, depth.length() - 2); // storing deoth - "ft" part
            index++; // index add 1 at time
        }
    }
   // return true;
    
}
void GameDriver::milestones(Inventory &i, Store &s) // function that takes care of all milestones 
{
    // variables 
    int food = 0;
    int distanceTraveled = 0;
    int choice;
    string temp;
    bool flag = false; // to keep resting repeatedly
    if(getMilesTraveled() >= stoi(mstones[msPassedCount][1])) // if miles are bigger or equal to a certaint milestone 
    {
        totalMiles = stoi(mstones[msPassedCount][1]);// sets your distance traveled to the milestone you just reached 
        if(mstones[msPassedCount][2] > "0")  // at  river if depth is bigger than 0
        {
            cout << endl;
            cout << "You got to " << mstones[msPassedCount][0] << endl; // printing out a river we are at
            cout << "The depth of this river is " << mstones[msPassedCount][2] << " feet" << endl;
            // options at the river 
            cout << "You have two options:" << endl;
            while (flag == false)
            {
                cout << "Keep picking until you choose to cross the river" << endl;
                cout << "1. Rest" << endl;
                cout << "2. Cross river" << endl;
                cout << "Please make a choice: ";
                getline(cin, temp); 
                choice = stoi(temp);
                if (choice == 1) // rest 
                {
                    cout << endl;
                    cout << "You chose to rest" << endl; 
                    d.addDates(1);
                    cout << "You had 1 days for rest" << endl;
                    food = -(1 * 3 * numPlayers); 
                    i.setFood(food); // food 
                    cout << "You have " << i.getFood() << " lbs of food left after resting for 1 day" << endl;
                    if (i.getFood() <= 0) // no food 
                    {
                        cout << "You have no food left! Game over" << endl;
                        printResults(i, d);
                    }
                    flag = false; // flag false so we can keep resting repeatedly
                }
                else if (choice == 2) // cross river 
                {
                    int cash;
                    cout << endl;
                    cout << "You chose to cross the river" << endl;
                    if (mstones[msPassedCount][2] > "3") // if depth is bigger than 3 use ferry
                    {
                        cash = (10 * numPlayers); 
                        i.setCash(-cash); // substructin cash for ferry
                        cout << "The river is deeper than 3ft so you need a ferry. It cost $10 per person" << endl;
                        cout << "You spent $" << cash << " to cross the river" << endl;
                
                    }
                    flag = true; // turn flag to true to get out of the loop
                    msPassedCount++;
                }
            }
            
        }
        else // you at a fort
        {
            cout << endl;
            cout << "You got to " << mstones[msPassedCount][0] << endl;
            cout << "You have three options" << endl;
            bool flag = false; // to rest and visit store repeatedly 
            while (flag == false)
            {
                cout << "Keep picking until you choose to continue on the trail" << endl;
                cout << "1. Rest" << endl;
                cout << "2. Visit store" << endl;
                cout << "3. Contine traveling" << endl;
                cout << "Please make a choice: ";
                getline(cin, temp); 
                choice = stoi(temp);
                if (choice == 1) // rest option
                {
                    cout << endl;
                    cout << "You chose to rest" << endl; 
                    d.addDates(1);
                    flag = false; // go back into loop
                    cout << "You had 1 days for rest" << endl;
                    food = -(1 * 3 * numPlayers); // instead of having 5 
                    i.setFood(food); // setting food
                    cout << "You have " << i.getFood() << " lbs of food left after resting for 1 day" << endl;
                    if (i.getFood() <= 0) // no food 
                    {
                        cout << "You have no food left! Game over" << endl;
                        printResults(i, d); // end game 
                    }
                }
                else if (choice == 2) // store option
                {
                    cout << endl;
                    cout << "You chose to visit the store" << endl;
                    s.shopMenu(i); // calling store function
                    flag = false; // go back into loop 
                    
                }
                else if (choice == 3) // continue on the trail option
                {
                    cout << endl;
                    cout << "You chose to continue on the trail" <<endl;
                    distanceTraveled = (rand() % 71) + 70;
                    cout << "You have traveled " << distanceTraveled << " miles" << endl;
                    // setting everything
                    d.addDates(14);
                    setMilesTraveled(distanceTraveled); 
                    food = -(14 * 3 * numPlayers);
                    i.setFood(food);
                    cout <<"You have " << i.getFood() << " lbs of food left after traveling for 2 weeks" << endl; 
                    flag = true; // to get out of the loop
    
                    if (i.getFood() <= 0) // if no food
                    {
                        cout << "You have no food left! Game over" << endl;
                        printResults(i, d); // end game 
                    }
                    msPassedCount++;
                }
            }
        }
    }
    else  //  did not reach a milestone
    {
        1; // since we need to have something in here but we do not want to do anything
    }
}
    