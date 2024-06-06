#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Book.h"
#include "User.h"
#include "Inventory.h"
#include "searchBook.h"
using namespace std;

//loadBooks initialize bookvector from bookdata.txt
void loadBooks(vector<Book> &bookVector) {
	system("cls");
	fstream inFile;
	inFile.open("bookdata.txt");

	if(!inFile.is_open()){
		cout << "bookdata error. Please try again later.";
		getchar();
		exit(1);
	}
	else	{cout << "Loading Book List..." << endl;}

	for(int i=0; !inFile.eof(); i++){
		Book bookHolder;
		int copy, ttlCopy;
		getline(inFile, bookHolder.bookID, '\t');
		getline(inFile, bookHolder.Title, '\t');
		getline(inFile, bookHolder.ISBN, '\t');
		inFile >> copy >> ttlCopy;
		inFile >> ws;
		bookHolder.inventory.setCopy(copy);
		bookHolder.inventory.setTotal(ttlCopy);
		
		bookVector.push_back(bookHolder);
	}

	inFile.close();
}

// bool login(Customer &customer){
// 	system("cls");
// 	fstream inFile;
// 	inFile.open("customerdata.txt");
// 	if(!inFile.is_open()){
// 		cout << "customerdata error. Please try again later.";
// 		getchar();
// 		exit(1);
// 	}

// 	string inputID,inputPsw,userID,userPsw;
// 	cout << "Enter User ID: ";
// 	cin >> inputID;
// 	cout << "Enter password: ";
// 	cin >> inputPsw;

// 	//Comparing user inputs with customerdata
// 	while(!inFile.eof()){
// 		getline(inFile,userID,'\t');
// 		if(inputID==userID){
// 			getline(inFile,userPsw,'\t');
// 			if(inputPsw==userPsw)	break;
// 			else{
// 				cout << "Wrong Password" << endl;
// 				system("pause");
// 				return false;
// 			}
// 		}
// 		else	getline(inFile,ws);
// 		if(inFile.eof()){
// 			cout << "User not found" << endl;
// 			system("pause");
// 			return false;
// 		}
// 	}

// 	//Fetching customerdata
// 	string userName;
// 	int numBook;
// 	string bookID, brwDate;
// 	getline(inFile,userName,'\t');
// 	inFile >> numBook;
// 	inFile >> ws;
// 	for(int i=0;i<numBook;i++){
//         string tempstr;
//         getline(inFile, tempstr, ',');
//         userHolder.books.push_back(tempstr);
//         inFile >> ws;
//     }

// 	return true;
// }

//User function 1. Search for books
//void searchBook(){
//	system("cls");
//	cout << "Search result";
//}

//Show user menu
int userFunction(vector<Book> &bookVector) {
	do{
		system("cls");

		int userAction;
		cout << "\t\tUser Menu" << endl;

		cout << "\t1. Search for books\n";
		cout << "\t2. Borrow books\n";
		cout << "\t3. Reservation\n";
		cout << "\t4. Check status\n";
		cout << "\t5. Logout\n\n";
		cout << "Enter action: ";
		cin >> userAction;

		switch (userAction)
		{
		case 1:
			searchBook(bookVector);
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
		case 5:
			cout << "Successfully logout..." << endl;
			system("pause");
			return 0;
		default:
			cout << "Please enter number between 1-5" << endl;
			system("pause");
			break;
		}

	}while(true);
	return 0;
}

void addBook(vector<Book> &bookVector) {

	fstream inFile;
	inFile.open("bookdata.txt", ios_base::app);

	string newID;
	string newTitle;
	string newISBN;
	int totalCopy;

	cout << "Enter ID of new book: ";
	cin >> newID;
	cin.ignore();

	cout << "Enter title of new book: ";
	getline(cin, newTitle);

	cout << "Enter ISBN of new book: ";
	cin >> newISBN;

	cout << "Enter the amount of copy: ";
	cin >> totalCopy;

	Book newBook(newID, newTitle, newISBN, totalCopy, totalCopy);
	bookVector.push_back(newBook);

	inFile << "\n" << newBook.getBookID() << "\t" << newBook.getTitle() << "\t" << newBook.getISBN() << "\t" << newBook.inventory.getInStock() << " " << newBook.inventory.getTotal();
}

void deleteBook(vector<Book>& bookVector) {
	string bookID;
    cout << "Enter the ID of the book to delete: ";
    cin >> bookID;

    auto it = find_if(bookVector.begin(), bookVector.end(), [&bookID](const Book& book) {
        return book.getBookID() == bookID;
    });

    if (it != bookVector.end()) {
        bookVector.erase(it);
        cout << "Book deleted successfully." << endl;

        // Update the database file
        ofstream outFile("bookdata.txt");
        if (outFile.is_open()) {
            for (const auto& book : bookVector) {
                outFile << book.getBookID() << "\t" << book.getTitle() << "\t" << book.getISBN() << "\t" << book.inventory.getInStock() << " " << book.inventory.getTotal() << endl;
            }
            outFile.close();
        } else {
            cout << "Error updating bookdata file." << endl;
        }
    } else {
        cout << "Book with ID " << bookID << " not found." << endl;
    }
    system("pause");
}


void adminFunction(vector<Book> &bookVector) {
	system("cls");
	cout << "\t\tAdmin Menu" << endl;

	int adminAction;
    do {
        cout << "\t1. Add Book\n";
        cout << "\t2. Delete Book\n";
        cout << "\t3. Exit Admin Menu\n";
        cout << "Enter action: ";
        cin >> adminAction;

        switch (adminAction) {
            case 1:
                addBook(bookVector);
                break;
            case 2:
                deleteBook(bookVector);
                break;
            case 3:
                return;
            default:
                cout << "Please enter number between 1-3" << endl;
                system("pause");
                break;
        }
    } while (true);
}

int main()
{
	vector<Book> bookVector;
	int actionNum;
	bool _loginSuccess=0;

	loadBooks(bookVector);
	
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
				//Customer customer;
				//_loginSuccess = login(customer);
				userFunction(bookVector);
				break;
			case 2:
				adminFunction(bookVector);
				break;
			case 3:
				return 0;
			default:
				cout << "Please enter number between 1-3" << endl;
				system("pause");
				break;
		}
	}while(true);

	return 0;
}


