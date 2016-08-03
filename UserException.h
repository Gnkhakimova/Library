#pragma once
#include <iostream>
using namespace std;


// exception class
class UserException
{
public:
    UserException(const string& exception);// = "exception in user class");
    string what() const;
private:
    string msg;
};