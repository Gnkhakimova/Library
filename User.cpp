#include "User.h"

//The ID number defaults to 0 and the first and last names to empty strings. This
//can be separate constructors or a single constructor with defaults for all parameters.
User::User(int newIDNumber)
{
    User user();
    IDNumber = newIDNumber;
    firstName = "";
    lastName = "";
    booksCheckedOut = nullptr;
    numberOfCheckedOut = 0;
    arraySize = 0;
}

User::User(string FirstName, string LastName)
{
    User user();
    IDNumber = 0;
    firstName = FirstName;
    lastName = LastName;
    booksCheckedOut = nullptr;
    numberOfCheckedOut = 0;
    arraySize = 0;
}


User::User()
{
    User user();
    IDNumber = 0;
    firstName = "";
    lastName = "";
    booksCheckedOut = nullptr;
    numberOfCheckedOut = 0;
    arraySize = 0;
}

// getter and setters
string* User::GetBooks()const
{
    return booksCheckedOut;
}
int User::GetIDNUmber() const
{
    return IDNumber;
}

string User::GetFirstName() const
{
    return firstName;
}

string User::GetLastName() const
{
    return lastName;
}

string User::GetFullName()const
{
    return (lastName + ", " + firstName);
}

void User::SetIDNumber(int NewNumber)
{
    if (NewNumber >= 100 && NewNumber < 1000000)
    {
        IDNumber = NewNumber;
    }
}

void User::SetFirstName(string NewFirstName)
{
    firstName = NewFirstName;
}

void User::SetLastName(string NewLastName)
{
    lastName = NewLastName;
}

// count of checked out books
int User::CheckoutCount()const
{
    return numberOfCheckedOut;
}
//Verifies that the BookIDCode is not already
//checked out, and adds it to the dynamic array of checked - out books(adjusting array size if
//   necessary).If the BookIDCode is already on the checked - out list, or for some reason the item
//   cannot be added, it returns false; if adding the item was successful, this function returns true
bool User::CheckOut(const string& BookIDCode)
{
    numberOfCheckedOut++;
    for (int i = 0; i < numberOfCheckedOut; i++) 
    {
        if (booksCheckedOut == nullptr)
        {
            if (numberOfCheckedOut >= arraySize)
            {
                try
                {
                    ResizeArray();
                    booksCheckedOut[numberOfCheckedOut-1] = BookIDCode;
                   
                    return true;
                }

                catch (exception e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
            }
        }
        
        else 
        {
            if (numberOfCheckedOut >= arraySize)
            {
                try
                {
                    ResizeArray();
                    booksCheckedOut[numberOfCheckedOut-1] = BookIDCode;
                    
                    return true;
                }

                catch (exception e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
            }
           
        }
       

    }
}

//Verifies that the BookIDCode is already on the
//checked - out list, and removes it.If this was the last item the user had checked out, the dynamic
//array is deleted.If the check - in was successful, this function returns true, otherwise it returns
//false.
bool User::CheckIn(const string& BookIDCode)
{
    bool returnValue = false;
    for (int i = 0; i < numberOfCheckedOut; i++)
    {
        if (booksCheckedOut[i] == BookIDCode)
        {
            booksCheckedOut[i] = "";
            returnValue = true;
        }
                      	
      }
    
    int nullcount=0;
    for (int j = 0; j < numberOfCheckedOut; j++)
    {
        if (booksCheckedOut[j].empty() == true)
        {
            nullcount++;
        }
    }
    if (nullcount == numberOfCheckedOut)
    {
        delete[] booksCheckedOut;
        booksCheckedOut = nullptr;
    }

    return returnValue;
}
    
//returns true if the BookIDCode is on
//the User's checked-out list, otherwise returns false. Does not change the object's data.
bool User::HasCheckedOut(const string& BookIDCode) const
 {
     for (int i = 0; i < numberOfCheckedOut; i++) // Loop to find the item to delete.
     {
         if (booksCheckedOut[i] == BookIDCode)
         {
             return true;
         }
         else
             return false;
     }
 }
 
//This method removes all of the object's data; the ID is set to 0, first and last name
//to empty strings, all checked - out data deleted, etc.
void User::Clear()
{
    IDNumber = 0;
    firstName = "";
    lastName = "";
    booksCheckedOut = nullptr;
    numberOfCheckedOut = 0;
    arraySize = 0;
        
     }

// destructor
User::~User()
{
    if (booksCheckedOut != nullptr)
    {
        delete[] booksCheckedOut;
        booksCheckedOut = nullptr;
    }
}
// overloading assigment operators
const User& User::operator=(const User& rhs)
{
    if (this != &rhs)
    {
        if (booksCheckedOut != nullptr)
        {
            delete[]booksCheckedOut;
            booksCheckedOut = nullptr;
        }
    }
        firstName = rhs.firstName;
        lastName = rhs.lastName;
        IDNumber = rhs.IDNumber;
        numberOfCheckedOut = rhs.numberOfCheckedOut;
        arraySize = rhs.arraySize;
        maxSize = rhs.maxSize;
        if (arraySize > 0)
        {
            booksCheckedOut = new string[arraySize];
            for (int i = 0; i < numberOfCheckedOut; i++)
            {
                booksCheckedOut[i] = rhs.booksCheckedOut[i];
            }
        }
        return *this;
    
}
//This is used as an alias for CheckOut
const User User::operator+(const User& rhs) const 
{
    User User2;
    User2.numberOfCheckedOut = numberOfCheckedOut + rhs.numberOfCheckedOut;
    return User2;
}
//Another alias for CheckOut
void User::operator+=(const string& rhs)
{
    User::CheckOut(rhs);

}

bool User::operator==(const User& rhs)
{
    if (IDNumber == rhs.IDNumber)
    {
        return true;
    }
    else
        return false;
}
bool User::operator!=(const User& rhs)
{
    if (IDNumber != rhs.IDNumber)
    {
        return true;
    }
    else
        return false;
}
//This is used to send the object's data out to an ostream. It is a friend
//function that takes a reference to an ostream and a const reference to a User as its parameters

const ostream& operator<<(ostream& os, const User& rhs)
{
    os << rhs.IDNumber << " " << rhs.firstName << " " << rhs.lastName << endl;
    os << rhs.numberOfCheckedOut << endl;
    if (rhs.numberOfCheckedOut > 0)
    {
        for (int i = 0; i < rhs.numberOfCheckedOut; i++)
        {
            os << rhs.booksCheckedOut[i] << " " << endl;
        }
    }
    return os;
}

//This is used to read the object's data from an istream. It is also a friend
//function and takes a reference to an istream and a reference to a User as its parameters.
const istream& operator>> (istream& is, User& rhs1)
{
    rhs1.Clear();
    is >> rhs1.IDNumber >> rhs1.firstName >> rhs1.lastName;
    is >> rhs1.numberOfCheckedOut;
    for (int i = 0; i < rhs1.numberOfCheckedOut; i++)
    {
        is >> rhs1.booksCheckedOut[i];
    }
    return is;
}

