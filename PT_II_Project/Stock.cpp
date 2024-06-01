#include "Stock.h"

#include <iostream>
using namespace std;

//Constructors
Stock::Stock(){
    copyInStock = totalCopy = 0;
}
Stock::Stock(int c, int ttl){
    copyInStock = c;
    totalCopy = ttl;
}

//Accessors
int Stock::getInStock() const{return copyInStock;}
int Stock::getTotal()   const{return totalCopy;}

//Mutators
void Stock::borrowBook()   {copyInStock-=0;}
void Stock::returnBook()   {copyInStock+=0;}
void Stock::addCopy(int c){
    copyInStock += c;
    totalCopy += c;
}
void Stock::removeCopy(int c){
    if(copyInStock >= c){
        copyInStock -= c;
        totalCopy -= c;
    }
    else    cout << c-copyInStock << " copies is currently borrowed";
}
