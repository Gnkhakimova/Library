#include"UserException.h"

// exception class implimentation file
UserException::UserException(const string& except = "exception in user class")
{
    msg = except;
}
string UserException::what() const
{
    return msg;
}