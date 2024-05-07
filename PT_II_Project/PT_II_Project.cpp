#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "Book.h"
using namespace std;

void userFunction() {
	system("cls");

	fstream inFile;
	inFile.open("database.txt");

	int userAction;
	cout << "\t\tMenu" << endl;

	cout << "\t1. Search for books\n";
	cout << "\t2. Borrow books\n";
	cout << "\t3. Reservation\n";
	cout << "\t4. Check status\n\n";
	cout << "Enter action: ";
	cin >> userAction;

	
}

void adminFunction() {
	system("cls");
	cout << "\t\tMenu";
}

int main()
{
	int actionNum;

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


