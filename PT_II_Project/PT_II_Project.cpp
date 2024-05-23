#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Book.h"
using namespace std;

void bootSystem(vector<Book> & bookVector) {
	system("cls");
	fstream inFile;
	inFile.open("database.txt");

	if(!inFile.is_open()){
		cout << "Database error. Please try again later.";
		exit(1);
	}
	else	{cout << "Loading Book List..." << endl;}

	for(int i=0; !inFile.eof();i++){
		Book bookHolder;
		getline(inFile, bookHolder.bookID, '\t');

		getline(inFile, bookHolder.Title, '\t');

		getline(inFile, bookHolder.ISBN);
		
		bookVector.push_back(bookHolder);
	}

	inFile.close();
}

void userFunction() {
	system("cls");

	int userAction;
	cout << "\t\tMenu" << endl;

	cout << "\t1. Search for books\n";
	cout << "\t2. Borrow books\n";
	cout << "\t3. Reservation\n";
	cout << "\t4. Check status\n\n";
	cout << "Enter action: ";
	cin >> userAction;

	switch (userAction)
	{
	case 1:
		bookList();
		break;
	case 2:
		cout << "WIP";
		break;
	case 3:
		cout << "WIP";
		break;
	default:
		break;
	}
}

void adminFunction() {
	system("cls");
	cout << "\t\tMenu";
}

int main()
{
	vector<Book> bookVector={};
	int actionNum;

	bootSystem(bookVector);
	
	cout << "ABC Library System" << endl;
	cout << "Please select an action: 1. Login as user" << endl;
	cout << "                         2. Login as admin" << endl;
	cout << "Enter action: ";
	cin >> actionNum;

	switch (actionNum)
	{
	case 1:
		userFunction();
		break;
	case 2:
		adminFunction();
		break;
	case 3:
		return 0;
		break;
	default:
		break;
	}


}


