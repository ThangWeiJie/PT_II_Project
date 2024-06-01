#ifndef USER_H
#define USER_H

#include <string>
#include "Book.h"
using namespace std;

class User{
private:
    string userID, password;
    bool _isAdmin;
    Book borrowedBooks;
public:

};

#endif