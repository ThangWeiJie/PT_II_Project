#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include "Book.h"
using namespace std;

const int MAX_RESULT_READ = 10;

string borderLine(){
    return (string(110,'-')+"\n");
}

string pop(string &str,int i){
    string temp;
    temp = str.substr(i,70);
    str.erase(i);
    return temp;
}

void showSearchResult(vector<Book> result, int p){
    cout << right << setw(50) << "Book List" << endl;
    cout << borderLine();
    cout << right << setw(5) << "No" << " |" << setw(7) << "ID" << setw(6) << "|" << setw(38) << "Title" << setw(33) << "|" << setw(8) << "ISBN" << endl;
    cout << borderLine();

    for(int i=0+(p*10);(i<result.size())&&(i<MAX_RESULT_READ+(p*10));i++){
        string titleL0 = result[i].getTitle();
        string titleL1 = " ";
        if(titleL0.length()>70){
            for(int j=70;j>0;j--){
                if(!isalpha(titleL0[j])){
                    titleL1 = pop(titleL0, j);
                    break;
                }
            }
        }

        cout << right << setw(5) << i+1 << ".| " << left << setw(11) << result[i].getBookID()  << "|" << setw(70) << titleL0 << "| "  << result[i].getISBN() << endl;
        cout << setw(6) << " " << "|" << setw(12) << " " << "|" << setw(70) << titleL1 << "| " << endl;
    }
    cout << borderLine();
}

void searchBook(vector<Book> books){
    string userSearch = "";
    int userAction = 1, page = 0, totalPage = 0, bookNo;
    bool _back = false;
    vector<Book> booksMatched;

    do{
        system("cls");

        for(int i=0;i<books.size();i++){
            if(books[i] == userSearch)  booksMatched.push_back(books[i]);
        }
        totalPage = ceil(booksMatched.size()/float(MAX_RESULT_READ));
        showSearchResult(booksMatched, page);

        cout << "\nSelect action:(1. Search book / 2. Borrow book / ";
        if(page<totalPage-1)    cout << "3. Next page / ";
        if(page>0)  cout << "4. Previous page / ";
        cout << "0. Back to user menu) " << endl << "=>";
        cin >> userAction;
        switch(userAction){
            case 1:
                cout << "\nSearch by Book Title, Author or ISBN: ";
                cin.ignore();
                getline(cin,userSearch);
                page = 0;
                break;
            case 2:
                cout << "\nInsert book no.:(1-" << booksMatched.size() << ") =>";
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
