/*

Name:	Gulnoza Khakimova
Course: CS 201R
Program: Library.
Due Date:	03/20/2016
Description:  A lending library is an example of this sort of situation. A user may have two dozen books checked out,
but on any given day, most users will not have any. Thus there is no point allocating memory for the
books these users have checked out. We will write a User class that has a dynamic array to hold
information about the books that User has checked out. (Since a library can have several copies of the
same book, just storing title and author isn't enough. We will assume that each book has a sticker with a
bar code representing a unique number; we can store books by bar code number.) 
Inputs: UserId, number of checked out books, book id.
Outputs: User id, number of checked out books, book id
Algorithm:
The User class will have the following public methods:
• Constructor method(s). 
• int GetIDNumber() const; 
• string GetFirstName() const; 

• string GetFullName() const; 
space, and then the first name. 
• Setters for IDNumber, FirstName, and LastName. 
• int CheckoutCount() const; 
• bool CheckOut(const string& BookIDCode); 
• bool CheckIn(const string& BookIDCode); 
• bool HasCheckedOut(const string& BookIDCode) const; 
• void Clear(). This method removes all of the object's data; the ID is set to 0, first and last name
to empty strings, all checked-out data deleted, etc.
• Because the object uses dynamic data, the User class will need a destructor and overloaded
assignment operator.
The User class has the following private data:
• strings for first and last name
• an unsigned int for the ID number
• unsigned ints for the number of books checked out and array size
• a string pointer (string*) to manage the dynamic array.
The User class has the following private method:
• bool ResizeArray(). 
The following invariant rules should hold across all methods:
• If there are no items checked out, the object should have no dynamic data array.
• The size of the array is greater or equal to the number of items checked out.
• If a dynamic array is full and another item checked out, the array must be expanded. The new
array should be twice as large as the old one.
• If there is no dynamic array and an item is checked out, make the dynamic array of size 5.
• If the array pointer is not nullptr, then it is pointing at validly-allocated memory; likewise, if
the memory has been deleted (i.e. no items are checked out), the array pointer should be nulled.

*/


#include "User.h"
#include <iostream>
using namespace std;

//add to .h
int CountUsers(ifstream& inputstream);
bool ParseTextFile(ifstream& inputstream, int NumberOfUsers, User* aUsers);
bool addCheckOuts(ifstream& in, User* aUsers, int numberOfUsers);
bool addCheckIns(ifstream& input, User* aUser, int numberOfUsers);


int main()
{
    int iNumberOfUsers = 0;
    string path2userstxt = "C:\\Users\\Gulnoza\\Desktop\\users.txt";
    string path2checkoutstxt = "C:\\Users\\Gulnoza\\Desktop\\checkouts.txt";
    string path2checkinstxt = "C:\\Users\\Gulnoza\\Desktop\\checkins.txt";
    string path2resulttxt = "C:\\Users\\Gulnoza\\Desktop\\User2.txt";
    // open input an doutput files
    ofstream fout;
    ifstream fin;

    ifstream fin3;
    ifstream fin4;

    fin.open(path2userstxt);
    fin3.open(path2checkoutstxt);
    fin4.open(path2checkinstxt);
    fout.open(path2resulttxt);


    iNumberOfUsers = CountUsers(fin); //get number of users

    //create array of users with data from CountUsers

    User* aUsers;
    aUsers = new User[iNumberOfUsers];

    //Add user data to array of users

    ifstream fin2;
    fin2.open(path2userstxt);

    ParseTextFile(fin2, iNumberOfUsers, aUsers);

    addCheckOuts(fin3, aUsers, iNumberOfUsers);
    addCheckIns(fin4, aUsers, iNumberOfUsers);

    for (int i = 0; i < iNumberOfUsers; i++)
    {
        fout << aUsers[i].GetIDNUmber() << "  " << aUsers[i].GetFirstName() << " "
            << aUsers[i].GetLastName() << endl;

        if (aUsers[i].CheckoutCount() == 0)
        {
            fout << aUsers[i].CheckoutCount() << endl;
        }
        else
        {

            fout << aUsers[i].CheckoutCount();
            for (int j = 0; j < aUsers[i].CheckoutCount(); j++)
            {
                fout << " " << aUsers[i].GetBooks()[j] << endl;
            }
            fout << endl;
        }
    }
}

//This function gets the steam of fileInput and returns the number of users
int CountUsers(ifstream& inputstream)
{
    string line="";
    int iNumberOfUsers = 0;
    
    while (getline(inputstream, line))
    {
        if (line == "0 " || line == " ")
        {
            iNumberOfUsers++;
        }
    }
    return iNumberOfUsers;
}

// get first name, last name, number of checked out books, book id
bool ParseTextFile(ifstream& inputstream, int NumberOfUsers, User* aUsers)
{
    try
    {
        int iCurrentUser = 0;
        string line = "";

        while (getline(inputstream, line))
        {
            string tmp = line;
           
                int spacePlace = line.find("  ");
                string tmpString = line.substr(0, spacePlace);
                if ((line != "0 " || line != " ") && tmpString.length()<7 && tmpString.length()>4)
                {
                    aUsers[iCurrentUser].SetIDNumber(stoi(tmpString));
                    string newString = line.substr(spacePlace + 2);
                    spacePlace = newString.find(" ");
                    string tmpString2 = newString.substr(0, spacePlace);
                    aUsers[iCurrentUser].SetFirstName(tmpString2);
                    string tmpString3 = newString.substr(spacePlace + 1);
                    aUsers[iCurrentUser].SetFirstName(tmpString3);

                }
               
                if ((tmpString != "0 " && tmpString != " ") && 
                    tmpString.length()<4 ||
                    
                    tmpString.length()>15)
                {
                    int a = tmpString.find(" ")+1;
                    aUsers[iCurrentUser].CheckOut(tmpString.substr(a));
                   
                }
                  else if (line == "0 ")
                {
                    iCurrentUser++;
                }
        

            
        }

        return true;
    }

        catch (exception e)
        {
            return false;
        }


    }
//what several users have checked out.It is in the form of a series
// of(UserID, ItemID) ordered pairs, with items separated by whitespace.

bool addCheckOuts(ifstream& in, User* aUsers, int numberOfUsers)
{
    while (in.good())
    {
        int userID;
        string itemID;
        in >> userID >> itemID;
        for (int i = 0; i < numberOfUsers; i++)
        {
            if (aUsers[i].GetIDNUmber() == userID)
            {
                bool resultb= aUsers[i].CheckOut(itemID);
                if (resultb == false)
                {
                    cerr << "No user can be found with this ID number: " << userID;
                   
                }
            }
           
        }
       
    }
    return true;
}
//several barcodes for
//items being checked in.Search the data array until you find the user who has that item checked out, and
//check it in using the class method.
bool addCheckIns(ifstream& input, User* aUser, int numberOfUsers)
{
    bool returnresult = false;
    while (input.good())
    {
        returnresult = false;
        string booksID;
        input >> booksID;
        for (int i = 0; i < numberOfUsers; i++)
        {
            if (aUser[i].CheckIn(booksID) == true)
            {
                returnresult=true;
            }
        }

        if (returnresult == false)
        {
            cerr << "No user can be found with this item checked out :" << booksID;
            return false;
        }
    }
    return returnresult;
    
}


