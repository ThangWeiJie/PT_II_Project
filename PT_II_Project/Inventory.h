#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
using namespace std;

class Inventory{
protected:
    int copyInStock, totalCopy;
public:
    //Constructors
    Inventory();
    Inventory(int, int);

    //Accessors
    int getInStock() const;
    int getTotal() const;

    //Mutators
    void setCopy(int);
    void setTotal(int);
    void borrowBook();
    void returnBook();
    void addCopy(int);
    void removeCopy(int);

    //Functions
    string status();

};

#endif