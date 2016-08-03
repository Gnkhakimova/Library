#include "UserException.h"
#include<iostream>
#include<string>
#include<fstream>


using namespace std;

typedef string* booksCheckedOut;

class User
{
public:
    //User(int newIDNumber, string newfirstName, string newlastName); //overloaded constructor
    User(int newIDNumber);
    User(string FirstName, string LastName);
    User();//default constructor
    int GetIDNUmber() const;
    string GetFirstName() const;
    string GetLastName() const;
    string GetFullName()const;
    void SetIDNumber(int NewNumber);
    void SetFirstName(string NewFirstName);
    void SetLastName(string NewLastName);
    int CheckoutCount()const;
    bool CheckOut(const string& BookIDCode);
    bool CheckIn(const string& BookIDCode);
    bool HasCheckedOut(const string& BookIDCode) const;
    void Clear();
    const User& operator=(const User& rhs);
    

    const User operator+(const User& rhs) const ;
    
    void  operator+=(const string& rhs);
    bool operator==(const User& rhs);
    bool operator!=(const User& rhs);
    string* GetBooks()const;
    ~User();
    
private:
    string firstName;
    string lastName;
    unsigned int IDNumber;
    unsigned int numberOfCheckedOut;
    unsigned int arraySize;
    int maxSize = 5;
    string* booksCheckedOut = new string[maxSize];
    
    //should be prepared to
    //catch a UserException from that method.If a UserException is caught, this method should print
    // a message to cerr and return false, indicating the object was not changed.
    bool ResizeArray()
    {
        try
        {
            bool returnValue = false;
            arraySize++;
            
            if (arraySize >=maxSize)
            {
                maxSize = arraySize * 2;
            }
            
            
            string *tempArray = new string[maxSize];
            for (int i = 0; i < arraySize; i++)
            {
                if (booksCheckedOut != nullptr)
                {
                    string tmp = tempArray[i];
                    string tmp2 = booksCheckedOut[i];
                    tempArray[i] = booksCheckedOut[i];
                    
                   
                }
            }

            delete[] booksCheckedOut;
            booksCheckedOut = nullptr;
            booksCheckedOut = tempArray;
            returnValue = true;
        }
        catch (exception)
        {
            throw UserException("exception in user class"); // default error message
        }
      
            
        
  
    }

    friend const ostream& operator<< (ostream& os, const User& rhs);
    friend const istream& operator>> (istream& is, User& rhs);
    
};

