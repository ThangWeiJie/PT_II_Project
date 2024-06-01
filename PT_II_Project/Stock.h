#ifndef STOCK_H
#define STOCK_H

using namespace std;

class Stock{
private:
    int copyInStock, totalCopy;
public:
    //Constructors
    Stock();
    Stock(int, int);

    //Accessors
    int getInStock() const;
    int getTotal() const;

    //Mutators
    void borrowBook();
    void returnBook();
    void addCopy(int);
    void removeCopy(int);

};

#endif