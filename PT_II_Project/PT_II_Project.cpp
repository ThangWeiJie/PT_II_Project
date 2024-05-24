#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Book.h"
using namespace std;

//bootSystem initialize bookvector and uservector from database in the main function
void bootSystem(vector<Book> & bookVector) {
	system("cls");
	fstream inFile;
	inFile.open("database.txt");

	if(!inFile.is_open()){
		cout << "Database error. Please try again later.";
		exit(1);
	}
	else	{cout << "Loading Book List..." << endl;}

	for(int i=0;!inFile.eof();i++){
		Book bookHolder;
		getline(inFile, bookHolder.bookID, '\t');

		getline(inFile, bookHolder.Title, '\t');

		getline(inFile, bookHolder.ISBN);
		
		bookVector.push_back(bookHolder);
	}

	inFile.close();
}

//User function 1. Search for books
void searchBook(){
	system("cls");
	cout << "Search result";
}

//Show user menu
void userFunction() {
	system("cls");

	int userAction;
	cout << "\t\tUser Menu" << endl;

	cout << "\t1. Search for books\n";
	cout << "\t2. Borrow books\n";
	cout << "\t3. Reservation\n";
	cout << "\t4. Check status\n\n";
	cout << "Enter action: ";
	cin >> userAction;

	switch (userAction)
	{
	case 1:
		searchBook();
		break;
	case 2:
		cout << "WIP" << endl;
		break;
	case 3:
		cout << "WIP" << endl;
		break;
	case 4:
		cout << "WIP" << endl;
		break;
	default:
		break;
	}
}



void adminFunction() {
	system("cls");
	cout << "\t\tAdmin Menu" << endl;
}

int main()
{
	vector<Book> bookVector={};
	int actionNum;

	bootSystem(bookVector);
	
	do{
		system("cls");
		cout << "ABC Library System" << endl;
		cout << "Please select an action: 1. Login as user" << endl;
		cout << "                         2. Login as admin" << endl;
		cout << "                         3. Exit program" << endl;
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
			default:
				cout << "Please enter number between 1-3" << endl;
				break;
		}
	}while(true);

	return 0;
}


