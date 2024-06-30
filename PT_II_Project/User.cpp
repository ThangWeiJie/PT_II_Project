#include "User.h"

#include <iostream>
using namespace std;

//Base Class User:
//Constructors
User::User(string ID="", string ps="", string n=""){
    userID = ID;
    password = ps;
    name = n;
}

//Mutators
void User::setID(string id)    {userID = id;}
void User::setPsw(string psw)   {password = psw;}
void User::setName(string n)    {name = n;}

//Accessors
string User::getID() const{ return userID; }
string User::getPsw() const{ return password; }
string User::getName() const{ return name; }


//Derived Class Customer:
//Constructors
Customer::Customer():User("","",""){}
Customer::Customer(string ID="", string ps="", string n="", int numBook = 0, vector<Book*> books={}, vector<tm> vectm={}) : User(ID,ps,n) {
    numBookBorrow = numBook;
    borrowedBooks = books;
    dueDateTm = vectm;
}

//Accessors
int Customer::getNumBookBorrow() const{ return numBookBorrow; }

string Customer::borrowDetails() const{
    string booksAndDates = "";
    for(int i=0; i<numBookBorrow; i++){
        booksAndDates += borrowedBooks[i]->getBookID();
        booksAndDates += ",";
        booksAndDates += dueDateString[i];
        if(i+1 < numBookBorrow)    booksAndDates += " ";
    }
    return booksAndDates;
}

//Mutators
void Customer::setNumBook(int n)    {numBookBorrow = n;}

//Functions
void Customer::borrowBook(Book *bookptr){
    system("cls");
    if(bookptr->inventory.getInStock()<=0){
        cout << "The book is currently out of stock" << endl;
        return;
    }
    int _confirm;
    bookptr->print();
    cout << "\n\t1. Confirm Borrowing this book\n";
    cout << "\t0. Back\n\n";
    cout << "Enter action: ";
    cin >> _confirm;
    if(_confirm == 0)   return;
    borrowedBooks.push_back(bookptr);
    numBookBorrow += 1;
    overDueDays.push_back(-14);
    overDueFees.push_back(0);
    bookptr->inventory.borrowBook();

    time_t dueTime = time(NULL);
    dueTime += SECS_PER_DAY*14;
    tm *duetm = localtime(&dueTime);
    char dueDate[100];
    strftime(dueDate, 50, "%Y%m%d", duetm);
    mkDueDateTm(string(dueDate));

    cout << "Borrowing Success!" << endl;
}

void Customer::returnBook(string bookID){
    for(int i=0; i<numBookBorrow; i++){
        if(borrowedBooks[i]->getBookID() == bookID){
            if(overDueFees[i] > 0){
                cout << "Please pay for overDue fee: RM" << overDueFees[i] << endl;
                cout << "Payment Received?(Y/N) -> ";
                cin.ignore();
                char _confirm;
                cin >> _confirm;
                if(!(_confirm=='Y'||_confirm=='y')){
                    cout << "Unable to return book.(Payment not received)" << endl;
                    system("pause");
                    return;
                }
            }
            borrowedBooks[i]->inventory.returnBook();
            numBookBorrow -= 1;
            dueDateTm.erase(dueDateTm.begin()+i);
            dueDateString.erase(dueDateString.begin()+i);
            overDueDays.erase(overDueDays.begin()+i);
            overDueFees.erase(overDueFees.begin()+i);
            cout << "Successfully return book:" << endl;
            borrowedBooks[i]->print();
            borrowedBooks.erase(borrowedBooks.begin()+i);
            system("pause");
            break;
        }
        else if(i+1 >= numBookBorrow){
            cout << "Book not found" << endl;
            system("pause");
        }
    }
}

void Customer::pointToBook(string bookID, vector<Book> &books){
    for(int i=0;i<books.size();i++){
        if(books[i].getBookID() == bookID)  borrowedBooks.push_back(&books[i]);
    }
}

void Customer::mkDueDateTm(string dateString){
    tm duetm={};
    int year,month,day;
    year = stoi(dateString.substr(0,4));
    month = stoi(dateString.substr(4,2));
    day = stoi(dateString.substr(6,2));

    duetm.tm_year = year - 1900;
    duetm.tm_mon = month - 1;
    duetm.tm_mday = day;

    dueDateTm.push_back(duetm);
    dueDateString.push_back(dateString);
}

void Customer::calculateOverDue(){
    for(int i=0;i<borrowedBooks.size();i++){
        time_t currTime = time(NULL);
        time_t dueTime = mktime(&dueDateTm[i]);

        int overDueDay = difftime(currTime,dueTime)/SECS_PER_DAY;
        overDueDays.push_back(overDueDay);

        int overDueFee = 0;
        if(overDueDay > 0)  overDueFee = overDueDay*OVERDUE_FEE_PER_DAY;
        else    overDueFee = 0;
        overDueFees.push_back(overDueFee);
    }
}

void Customer::print(){
    cout << "Personal Details: " << endl;
    cout << "User ID: " << userID << "\tName: " << name << endl;
    cout << "Borrowed Books: " << numBookBorrow << " Books:" << endl << endl;
    char dueDate[100];
    int totalFee = 0;
    for(int i=0;i<numBookBorrow;i++){
        strftime(dueDate, 50, "%d %B %Y", &dueDateTm[i]);
        cout << "Book#" << i+1 << ": Title: " << borrowedBooks[i]->getTitle() << endl;
        cout << "\tDue Date: " << dueDate << endl;
        if(overDueDays[i]>0){
            cout << "\tOverDue: " << overDueDays[i] << " days\tOverdueFee= RM" << overDueFees[i];
            totalFee += overDueFees[i];
        }
        cout << endl << endl;
    }
    cout << "Total overdue Fees = RM" << totalFee << endl;
}

//Derived Class Admin:
//Constructors
Admin::Admin():User("","",""), adminLevel(0){}

Admin::Admin(string ID="", string ps="", string n="", int lvl=0) : User(ID,ps,n) , adminLevel(lvl){}

void Admin::setAdminLvl(int lvl) { adminLevel = lvl; }