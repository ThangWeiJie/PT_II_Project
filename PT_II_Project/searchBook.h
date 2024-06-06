#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include "Book.h"
using namespace std;

const int MAX_RESULT_READ = 10;
const int TITLE_LENGTH_perROW = 63;

string borderLine(){
    return (string(110,'-')+"\n");
}

string pop(string &str,int i){
    string temp;
    temp = str.substr(i,TITLE_LENGTH_perROW);
    str.erase(i);
    return temp;
}

void showSearchResult(vector<Book *> result, int p){
    cout << right << setw(60) << "Book List" << endl;
    cout << borderLine();
    cout << right << setw(5) << "No" << " |" << setw(6) << "ID" << setw(6) << "|" << setw(TITLE_LENGTH_perROW/2+3) << "Title" << setw(TITLE_LENGTH_perROW/2-1) << "|"
        << setw(9) << "ISBN" << setw(7) << "|" << setw(8) << "Status" << endl;
    cout << borderLine();

    for(int i=(p*10);(i<result.size())&&(i<MAX_RESULT_READ+(p*10));i++){
        string titleL0 = result[i]->getTitle();
        string titleL1 = " ";
        if(titleL0.length()>TITLE_LENGTH_perROW){
            for(int j=TITLE_LENGTH_perROW;j>0;j--){
                if(!isalpha(titleL0[j])){
                    titleL1 = pop(titleL0, j);
                    break;
                }
            }
        }

        cout << right << setw(5) << i+1 << ".| " << left << setw(10) << result[i]->getBookID()  << "|" << setw(TITLE_LENGTH_perROW) << titleL0 << "| " 
            << setw(13) << result[i]->getISBN() << " | " << result[i]->inventory.status() << endl;
        cout << right << setw(7) << "|" << setw(12) << "|" << left << setw(TITLE_LENGTH_perROW) << titleL1 << "|               |" << endl;
    }
    cout << borderLine();
}

void searchBook(vector<Book> books){
    string userSearch = "";
    int userAction = 1, page = 0, totalPage = 0, bookNo;
    bool _back = false;
    vector<Book *> booksMatched;

    do{
        system("cls");

        for(int i=0;i<books.size();i++){
            if(books[i] == userSearch)  booksMatched.push_back(&books[i]);
        }
        totalPage = ceil(booksMatched.size()/float(MAX_RESULT_READ));
        showSearchResult(booksMatched, page);

        cout << "Searching keyword: " << left << setw(13) << userSearch.substr(0,10)+((userSearch.length()>10)? "...":"") << right << setw(77) << "Page " + to_string(page+1) + "/" + to_string(totalPage) << endl;
        cout << "\nSelect action:(1. Search book / 2. Borrow book / " << ((page<totalPage-1)? "3. Next page / " : "") 
             << ((page>0)? "4. Previous page / " : "") << "0. Back to user menu)" << endl << "=>";
        cin >> userAction;
        switch(userAction){
            case 1:
                cout << "\nSearch by Book ID, Book Title or ISBN: ";
                cin.ignore();
                getline(cin,userSearch);
                page = 0;
                break;
            case 2:
                cout << "\nInsert the No. of book:(1-" << booksMatched.size() << ") ";
                cin >> bookNo;
                break;
            case 3:
                if(page<totalPage-1) page+=1;
                break;
            case 4:
                if(page>0) page-=1;
                break;
            case 0:
                _back = true;
                break;
            default:
                cout << "Invalid Action Number" << endl;
                system("pause");
                break;
        }
        
        booksMatched.clear();
    }while(!_back);
        system("pause");
}