#include "Inventory.h"

#include <iostream>
using namespace std;

//Constructors
Inventory::Inventory(){
    copyInStock = totalCopy = 0;
}
Inventory::Inventory(int c, int ttl){
    copyInStock = c;
    totalCopy = ttl;
}

//Accessors
int Inventory::getInStock() const{return copyInStock;}
int Inventory::getTotal()   const{return totalCopy;}

//Mutators
void Inventory::setCopy(int c)   {copyInStock = c;}
void Inventory::setTotal(int ttl)   {totalCopy = ttl;}
void Inventory::borrowBook()   {copyInStock-=0;}
void Inventory::returnBook()   {copyInStock+=0;}
void Inventory::addCopy(int c){
    copyInStock += c;
    totalCopy += c;
}
void Inventory::removeCopy(int c){
    if(copyInStock >= c){
        copyInStock -= c;
        totalCopy -= c;
    }
    else    cout << c-copyInStock << " copies is currently borrowed";
}

//Functions
string Inventory::status(){
    if(copyInStock>0)   return "Available";
    else    return "OutOfStock";
}