#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include "Stock.h"
using namespace std;

class Book {
private:
	string bookID;
	string Title;
	string ISBN;

public:
	Stock stock;
	//Constructors
	Book();
	Book(string, string, string);

	//Mutators
	void setBookID(string);
	void setTitle(string);
	void setISBN(string);
	//Accessors
	string getBookID() const;
	string getTitle() const;
	string getISBN() const;

	//Functions
	string toUpper(string);

	//Overloaded operators
	bool operator==(string);


	friend void loadBooks(vector<Book>&);

	~Book() {};
};


#endif 

