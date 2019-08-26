#include <string>
using namespace std;

#ifndef Date_H
#define Date_H

class Date
{
    
    public:
        
        Date();
        
        void setStartDate(int, int, int);
        int getStartMonth();
        void userPicksDate();
        int getStartDay();
        void addDates(int);
        
    private:
        
        int day;
        int month;
        int year;
      
    
};

#endif