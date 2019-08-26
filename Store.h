#include "Inventory.h"

#ifndef Store_H
#define Store_H

using namespace std; 

class Store
{
   public:
     
      Store();
   
      int getItems();
      void display();
      void shopMenu(Inventory &);
      void setTotal(double);
      double getTotal();
      
      

   private:
   
      int numItems;
      double totalPrice;
      double price;
      double yoke;
      double food;
      double bullets;
      double medKit;
      double wagonParts;
      double total;
      double newAmount;
      double scalars;
      
      
   
};

#endif
