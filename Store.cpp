#include <iostream>
#include <iomanip>
#include <string>

#include "Store.h"

using namespace std;

Store s;

Store::Store()   // default constructor 
{
    numItems = 0;
    totalPrice = 0;
    yoke = 40.00;
    food = 0.50; 
    bullets = 2.00;
    wagonParts = 20.00;
    medKit = 25.00;
   
}

void Store::setTotal(double addedBill) // setting total price
{
    totalPrice = totalPrice + addedBill;
}
double Store::getTotal() // getting total price 
{
    return totalPrice;
}

void Store::shopMenu(Inventory &i) // shop menu basically all shopping is done here 
{

	cout << "Welcome to the store. Please pick what you want to buy: " << endl << endl;
	string choice;
	double newOxen = 0.0; // setting everything to 0
	double newFood = 0.0;
	double newBullets = 0.0;
	double newMed = 0.0;
	double newParts = 0.0;
	
   	while (choice != "6") 
    {
        cout << endl; // menu
        cout << "=======================" << endl;
    	cout << "=======Shop Menu=======" << endl;
    	cout << "=======================" << endl;
    	cout << "1.Oxens           $" << newOxen << endl;
    	cout << "2.Food            $" << newFood << endl;
    	cout << "3.Bullets         $" << newBullets << endl;
    	cout << "4.Medical Kit     $" << newMed << endl;
    	cout << "5.Wagon Parts     $" << newParts << endl;
    	cout << "6.Done shopping" << endl;
    	cout << "=======================" << endl;
    	cout << "Your total bill is $" << getTotal() << endl;
    	cout << "You have $" << i.getCash() << endl;
        // variables setting
        string number;
        string pounds;
        string boxes;
        string kits;
        string parts;
        double amount;
        double total;
        getline(cin, choice);
        
        switch (stoi(choice)) // switch cases for a menu 
        {
            case 1: // buying oxens
            
            cout << endl;
            cout << "There are two oxens in a yoke" << endl;
            cout << "You need at least three oxens" << endl;
            cout << "One yoke cost $40" << endl;
            cout << "Please enter how many yokes you want to buy: ";
            getline(cin, number); // input 
            amount = yoke * stoi(number); // price for oxen and yokes
           
            while ((stoi(number) + i.getOxen()) < 3 || (stoi(number) + i.getOxen()) > 5) // edge cases need to buy in between 3 and 5
            {
                if (amount > i.getCash()) // edge case if not having enough money
                {
                    cout << "You do not have enough money" << endl;
                }
                else if ((stoi(number) + i.getOxen()) < 3 || (stoi(number) + i.getOxen()) > 5) // edge case to buy in between 100 and 200
                {
                    cout << "You need to spend on oxen in between $100 and $200" << endl;
                }
                cout << "Please enter a different amount: "; // next input if previous was incorrect
                getline(cin, number);
                amount = yoke * stoi(number);
            }
                    
                cout << "You bought " << stoi(number) << " yokes" << endl;
                cout << "You bought " << stoi(number) * 2 << " oxens" << endl;
                i.setOxen(stoi(number)); // setting oxens
                amount = yoke * stoi(number);
                newOxen = newOxen + amount;
                setTotal(amount); // setting total
                numItems++;
            
            break;
            
            case 2:
            
            cout << endl; // buying food per pound
            cout << "A pound of food cost $0.50" << endl;
            cout << "Please enter how many pounds of food you want to buy: ";
            getline(cin, pounds); // input
            amount = food * stoi(pounds);
            
            while (stoi(pounds) > 1000 || amount > i.getCash()) // edge cases
            {
                if (amount > i.getCash()) // when not enough money 
                {
                    cout << "You do not have enough money" << endl;
                }
                else if (stoi(pounds) > 1000) // when buying too much
                {
                    cout << "You cannot buy more than 1000lbs but we recommend for each person 150lbs" << endl;
                }
                cout << "Please enter a different amount: ";
                getline(cin, pounds); // new input if previous incorrect
                amount = food * stoi(pounds);
            }
            
            cout << "You bought " << pounds << " lbs of food" << endl;
            amount = food * stoi(pounds);
            newFood = newFood + amount;
            i.setFood(stoi(pounds)); // setting food
            setTotal(amount); //setting total price
            numItems++;
            break;
            
            case 3:
            
            cout << endl; // buying bullets boxes 
            cout << "A box of 20 bullets cost $2.00" << endl;
            cout << "Please enter how many boxes you want to buy: ";
            getline(cin, boxes);
            amount = bullets * stoi(boxes);
            
            while (amount > i.getCash()) // edge case if not enough money
            {
                cout << "You do not have enough money" << endl;
                cout << "Please enter a different amount: ";
                getline(cin, boxes);
                amount = bullets * stoi(boxes);
            }
            
            cout << "You bought " << boxes << " boxes of bullets, so you have " << 20 * stoi(boxes) << " bullets" << endl;
            i.setBullets(stoi(boxes) * 20); // setting bullets
            amount = bullets * stoi(boxes);
            newBullets = newBullets + amount;
            setTotal(amount); // setting total price 
            numItems++;
            break;
            
            case 4:
            
            cout << endl; // buying medical kits
            cout << "One medical kit cost $25.00" << endl;
            cout << "Please enter how many medical kits you want to buy: ";
            getline(cin, kits);
            amount = medKit * stoi(kits);
            
            while (amount > i.getCash()) // edge case not enough maney
            {
                cout << "You do not have enough money" << endl;
                cout << "Please enter a different amount: ";
                getline(cin, kits);
                amount = medKit * stoi(kits);
                
           }

            cout << "You bought "<< kits << " medical Kits" << endl;
            i.setMedKit(stoi(kits)); // setting medical kits
            newMed = newMed + amount;
            setTotal(amount); // setting total price
            numItems++;
            break;
            
            case 5:
            
            cout << endl; // buying wagon parts
            cout << "Wagon parts include wheels, axles and tongues" << endl;
            cout << "One wagon part cost $20" << endl;
            cout << "Please enter how many wagon parts you want to buy: ";
            getline(cin, parts);
            amount = wagonParts * stoi(parts);
            
            while (amount > i.getCash()) //edge case not enough money
            {
                cout << "You do not have enough money" << endl;
                cout << "Please enter a different amount: ";
                getline(cin, parts);
                amount = wagonParts * stoi(parts);
                
           }

            cout << "You bought " << parts << " wagon parts" << endl;
            newParts = newParts + amount;
            i.setWagonParts(stoi(parts)); // setting wagon parts
            setTotal(amount); //setting total price 
            numItems++;
            break;
            
            
            case 6:
            i.setCash(-totalPrice); // when done shopping setting cash so cash minus total bill
            cout << endl;
            cout << "You are done shopping. Thank you" << endl;
            cout << "You have $" << i.getCash() << " left" << endl;
            cout << endl;
            cout << endl;
            break;
            
            default:
                cout << "invalid input" << endl;
          
        }
                
    }
  
}


int Store::getItems() // getting number of items 
{
   return numItems; 
}


void Store::display() // displaying first cout for wagon purshase
{
      cout << "You have just bough wagon that cost $200.00. Your have $1000.00 left." << endl;
}

