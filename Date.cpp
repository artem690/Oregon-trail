#include <iostream>
#include <iomanip>
#include <string>


#include "Date.h"

using namespace std;

Date::Date() // default constructor 
{
    month = 0;
    day = 0;
    year = 1847;
}


void Date::setStartDate(int months, int days, int years) // setting date month and year but year is always the same
{
    month = months;
    day = days;
    year = years;
}
int Date::getStartMonth() // return
{
    return month;
}
int Date::getStartDay() // return
{
    return day;
}

void Date::userPicksDate() // a function for if user wants to pick his own date of start
{
    string startDate;
    char YesOrNo; // char for yes or no
    int day;
    string temp;
    int month = -1;
    cout << "You can start on default date 03/28/1847 or You can also choose a different departure date between 03/01/1847 and 05/01/1847." << endl;    
    cout << "Start on 03/28/1847 ?" << endl;
    cout << "Please enter (y) or (n): ";
    getline(cin, temp);
    YesOrNo = temp[0]; // to make it char
    
    if (YesOrNo == 'y' || YesOrNo == 'Y') // if yes then default date set
    {
        setStartDate(03, 28, 1847); // using function to set
        cout << "Your start date is 03/28/1847" << endl;
    }
    else if (YesOrNo == 'n' || YesOrNo == 'N') // if not pick your own date 
    {
        cout << "You chose to pick a different start date" << endl; 
        cout << "Please enter month: ";
        getline(cin, temp);
        month = stoi(temp);
        
        while (month > 5 || month < 3) // edge case to start in between certaint dates 
        {
            cout << "Invalid month. Input again: "; // keep inputing for cerrect input 
            getline(cin, temp);
            month = stoi(temp);
        }
        cout << "Please enter day: ";
        getline(cin, temp);
        day = stoi(temp);
        while (day > 31 || day < 1) // edge case to start in between certaint dates 
        {
            cout << "Invalid day. Input again: "; // keep inputing for cerrect input 
            getline(cin, temp);
            day = stoi(temp);
        }
        setStartDate(month, day, 1847); // setting start date that was picked 
        cout << "Here is your chosen start date " << getStartMonth() << "/" << getStartDay() << "/1847"  << endl;
    }
}
      
void Date::addDates(int newDay) // add dates while taking turns 
{
    day = day + newDay;
    switch (month)  // switch cases for differrent months 
    {
        
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day > 31) 
            {
                day = day - 31; // substricting to find out how many gone over so it goes into next month // days 
                month++; // next month if days 31 or more 
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30)
            {
                day = day - 30; // substricting to find out how many gone over so it goes into next month // days
                month++; // next month if days 30 or more 
            }
            break;
        default:
            if (day > 28) // for february which we do no need 
            {
                month++;   
            }
        
    }
  
}

