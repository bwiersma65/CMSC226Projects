//
//  invmenu.cpp
//  Semester Project
//
//  Created by Ben Wiersma on 2/10/20.
//  Copyright © 2020 Ben Wiersma. All rights reserved.
//

#include <iostream>
#include <string>
// header files
#include "invmenu.h"
#include "bookinfo.h"
using namespace std;

/*
Global arrays for holding data on each book
*/
const int NUM_OF_ITEMS = 20;
const int TITLE_LENGTH = 51, ISBN_LENGTH = 14, NAME_LENGTH = 31, DATE_LENGTH = 11;
extern char bookTitle[NUM_OF_ITEMS][TITLE_LENGTH], isbn[NUM_OF_ITEMS][ISBN_LENGTH], author[NUM_OF_ITEMS][NAME_LENGTH], publisher[NUM_OF_ITEMS][NAME_LENGTH], dateAdded[NUM_OF_ITEMS][DATE_LENGTH];
extern int qtyOnHand[NUM_OF_ITEMS];
extern double wholesale[NUM_OF_ITEMS], retail[NUM_OF_ITEMS];
extern int bookCounter;

int invMenu()
{
    int input = 0;
    
    do {
        // Menu Screen
        cout << "\n////////////////////////////////////////////////////////////////////////////";
        cout << "\n\t\t\tSerendipity Booksellers\n\t\t\t  Inventory Database" << endl;
        cout << "\n\t\t\t1.  Look Up a Book" << endl;
        cout << "\t\t\t2.  Add a Book" << endl;
        cout << "\t\t\t3.  Edit a Book's Record" << endl;
        cout << "\t\t\t4.  Delete a Book" << endl;
        cout << "\t\t\t5.  Return to the Main Menu" << endl;
        cout << "\n\t\t\tEnter Your Choice: ";
        
        cin >> input;
        
        // Input Validation
        while (input < 1 || 5 < input)
        {
            cout << "\n\t\t\tPlease enter a number in the range 1 - 5" << endl;
            cout << "\n\t\t\tEnter Your Choice: ";
            cin >> input;
        }
        
        /*
         Menu selection
         */
        switch (input)
        {
            case 1: lookUpBook();
                break;
            case 2: addBook();
                break;
            case 3: editBook();
                break;
            case 4: deleteBook();
                break;
            case 5: cout << "\n\t\t\tYou selected item 5\n";
        }
    }
    while (input != 5);
    return 0;
}

/*
 Searches for book with given title, then prints book info
 */
void lookUpBook()
{
    cout << "\n////////////////////////////////////////////////////////////////////////////";
    char searchTitle[TITLE_LENGTH];
    bool found;
    int index, i = 0;
    char *titlePtr = nullptr;
    char correct = 'q', kontinue = 'z';
    
    
    do {
        cin.ignore();
        cout << "\nPlease enter book title: ";
        cin.getline(searchTitle, TITLE_LENGTH);
        strUpper(searchTitle);
        index = -1;
        found = false;
        while (!found && i < bookCounter) {
            /*
             Check if input text matches portion of book title from inventory
             */
            titlePtr = strstr(bookTitle[i], searchTitle);
            if (titlePtr != nullptr) {
                found = true;
                index = i;
            }
            i++;
        }
        /*
         Check to ensure this is book user wants
         */
        if (found) {
            cout << "Is this the book you're looking for? (Y/N): ";
            cout << bookTitle[index] << endl;
            cin >> correct;
            if (correct == 'N' || correct == 'n')
                found = false;
        }
        /*
         Print error msg if title matching text could not be found in database
         */
        else {
            i = 0;
            cout << "Book could not be found, try again? (Y/N): ";
            cin >> kontinue;
        }
    }
    while ((correct == 'N' || correct == 'n' || kontinue == 'Y' || kontinue == 'y') && i < bookCounter);
    
    /*
     Book not found and end of inventory reached
     */
    if (!found && i == bookCounter) {
        cout << "\nBook with given title could not be found" << endl;
        return;
    }
    /*
     Prints book info
     */
    else
        bookInfo(isbn[index], bookTitle[index], author[index], publisher[index], dateAdded[index], qtyOnHand[index], wholesale[index], retail[index]);
}

/*
 Searches for empty space in inventory database, then requests input for data of the book being entered
 */
void addBook()
{
    char titleTemp[TITLE_LENGTH], isbnTemp[ISBN_LENGTH], authorTemp[NAME_LENGTH], pubTemp[NAME_LENGTH];
    cin.ignore();
    cout << "\n////////////////////////////////////////////////////////////////////////////";
    /*
     Searches array for empty slot
     */
    int index = -1;
    for (int i = 0; i < 20; i++) {
        if (strcmp(bookTitle[i], "") == 0) {
            index = i;
            break;
        }
    }
    
    /*
     Database full
     */
    if (index == -1) {
        cout << "\nThe array is full. No more books may be added" << endl;
        return;
    }
    /*
     Prompts for book data to be added to program array
     */
    else {
        cout << "\nPlease enter the following informatin:\n" << endl;
        cout << "Book Title: ";
        cin.getline(titleTemp, TITLE_LENGTH);
        strUpper(titleTemp);
        strcpy(bookTitle[index], titleTemp);
        cout << "\nISBN Number: ";
        //getline(cin, isbn[index]);
        //cin.getline(isbn[index], ISBN_LENGTH);
        cin.getline(isbnTemp, ISBN_LENGTH);
        strUpper(isbnTemp);
        strcpy(isbn[index], isbnTemp);
        cout << "\nAuthor's Name: ";
        //getline(cin, author[index]);
        cin.getline(authorTemp, NAME_LENGTH);
        strUpper(authorTemp);
        strcpy(author[index], authorTemp);
        cout << "\nPublisher's Name: ";
        //getline(cin, publisher[index]);
        cin.getline(pubTemp, NAME_LENGTH);
        strUpper(pubTemp);
        strcpy(publisher[index], pubTemp);
        cout << "\nDate book was added to inventory (MM-DD-YYYY): ";
        //getline(cin, dateAdded[index]);
        cin.getline(dateAdded[index], DATE_LENGTH);
        cout << "\nQuantity of book being added: ";
        cin >> qtyOnHand[index];
        cout << "\nWholesale cost of (single) book: ";
        cin >> wholesale[index];
        cout << "\nRetail price of (single) book: ";
        cin >> retail[index];
        
        /*
         Increments counter to reflect new book has been added to database
         */
        bookCounter++;
    }
}

/*
 Searches for book in array, then asks if user would like to edit piece of book data
 */
void editBook()
{
    cout << "\n////////////////////////////////////////////////////////////////////////////";
    
    char title[TITLE_LENGTH], isbnTemp[ISBN_LENGTH], titleTemp[TITLE_LENGTH], authorTemp[NAME_LENGTH], pubTemp[NAME_LENGTH];
    int menuChoice;
    char kontinue = 'z';
    bool found;
    int index = -1;
    char *titlePtr = nullptr;
    char correct = 'q';
    
    do {
        cin.ignore();
        cout << "\nPlease enter book title: ";
        cin.getline(title, TITLE_LENGTH);
        strUpper(title);
        found = false;
        /*
         Check if input text matches portion of title from database
         */
        while (!found && index < bookCounter)
        {
            titlePtr = strstr(bookTitle[index], title);
            if (titlePtr != nullptr)
                found = true;
            else
                index++;
        }
        
        /*
         Check to ensure this is book user wants
         */
        if (found) {
            cout << "Is this the book you're looking for? (Y/N): " << endl;
            cout << bookTitle[index] << endl;
            cin >> correct;
        }
        /*
         Book title could not be found in database
         */
        else {
            index = 0;
            cout << "Book could not be found. Try again? (Y/N): " << endl;
            cin >> kontinue;
        }
    }
    while ((correct == 'N' || correct == 'n' || kontinue == 'Y' || kontinue == 'y') && index < bookCounter);
    
    /*
     Book not found and inventory exhausted
     */
    if (!found && index == bookCounter) {
        cout << "\nBook with given title could not be found" << endl;
        return;
    }
    else {
        do {
            /*
             Print current book info
             */
            bookInfo(isbn[index], bookTitle[index], author[index], publisher[index], dateAdded[index], qtyOnHand[index], wholesale[index], retail[index]);
            
            menuChoice = -1;
            
            /*
             Prompt for book datum to be changed
             */
            cout << "\nWhich fields would you like changed?\n\n";
            cout << "1 - ISBN" << endl;
            cout << "2 - Title" << endl;
            cout << "3 - Author" << endl;
            cout << "4 - Publisher" << endl;
            cout << "5 - Date Added" << endl;
            cout << "6 - Quantity-on-Hand" << endl;
            cout << "7 - Wholesale Cost" << endl;
            cout << "8 - Retail Price" << endl;
            cout << "9 - Cancel" << endl;
            cout << "\nSelection: ";
            cin >> menuChoice;
            
            switch (menuChoice)
            {
                case 1:
                    cin.ignore();
                    cout << "\nEnter the new ISBN: ";
                    cin.getline(isbnTemp, ISBN_LENGTH);
                    strUpper(isbnTemp);
                    strcpy(isbn[index], isbnTemp);
                    break;
                case 2:
                    cin.ignore();
                    cout << "\nEnter the new Title: ";
                    //getline(cin, bookTitle[index]);
                    cin.getline(titleTemp, TITLE_LENGTH);
                    strUpper(titleTemp);
                    strcpy(bookTitle[index], titleTemp);
                    break;
                case 3:
                    cin.ignore();
                    cout << "\nEnter the new Author: ";
                    //getline(cin, author[index]);
                    cin.getline(authorTemp, NAME_LENGTH);
                    strUpper(authorTemp);
                    strcpy(author[index], authorTemp);
                    break;
                case 4:
                    cin.ignore();
                    cout << "\nEnter the new Publisher: ";
                    //getline(cin, publisher[index]);
                    cin.getline(pubTemp, NAME_LENGTH);
                    strUpper(pubTemp);
                    strcpy(publisher[index], pubTemp);
                    break;
                case 5:
                    cin.ignore();
                    cout << "\nEnter the new Date Added: ";
                    //cin >> dateAdded[index];
                    cin.getline(dateAdded[index], DATE_LENGTH);
                    break;
                case 6:
                    cout << "\nEnter the new Quantity-On-Hand: ";
                    cin >> qtyOnHand[index];
                    break;
                case 7:
                    cout << "\nEnter the new Wholesale Cost: ";
                    cin >> wholesale[index];
                    break;
                case 8:
                    cout << "\nEnter the new Retail Price: ";
                    cin >> retail[index];
                    break;
                case 9:
                    break;
            }
            
            /*
             Reprint new book data
             */
            bookInfo(isbn[index], bookTitle[index], author[index], publisher[index], dateAdded[index], qtyOnHand[index], wholesale[index], retail[index]);
            
            /*
             Prompt for loop
             */
            cout << "\nWould you like to change another field? (Y/N): ";
            cin >> kontinue;
        }
        while (kontinue == 'Y' || kontinue == 'y');
    }
}

/*
 Deletes given book and its data from inventory
 */
void deleteBook()
{
    cout << "\n////////////////////////////////////////////////////////////////////////////";
    char title[TITLE_LENGTH];
    
    /*
     Searches array for book with given title
     */
    bool found;
    int index = -1;
    char *titlePtr = nullptr;
    char correct = 'q', kontinue = 'r', erase = 'z';

    do {
        cin.ignore();
        cout << "\nPlease enter book title: ";
        //getline(cin, title);
        cin.getline(title, TITLE_LENGTH);
        strUpper(title);
        found = false;
        /*
         Check if input text matches portion of title from inventory
         */
        while (!found && index < bookCounter)
        {
            titlePtr = strstr(bookTitle[index], title);
            if (titlePtr != nullptr)
                found = true;
            else
                index++;
        }
        
        /*
         Check to ensure this is book user wants
         */
        if (found) {
            cout << "Is this the book you're looking for? (Y/N): " << endl;
            cout << bookTitle[index] << endl;
            cin >> correct;
        }
        /*
         Title not found in inventory database
         */
        else {
            index = 0;
            cout << "Book could not be found. Try again? (Y/N): " << endl;
            cin >> kontinue;
        }
    }
    while ((correct == 'N' || correct == 'n' || kontinue == 'Y' || kontinue == 'y') && index < bookCounter);
    
    /*
     Book not found and inventory exhausted
     */
    if (!found && index == bookCounter) {
        cout << "\nBook with given title could not be found" << endl;
        return;
    }
    else {
        bookInfo(isbn[index], bookTitle[index], author[index], publisher[index], dateAdded[index], qtyOnHand[index], wholesale[index], retail[index]);
        cout << "\nAre you sure this book is to be deleted from inventory? (Y/N): ";
        cin >> erase;
        
        /*
         Sets book data to default values (empty string or 0)
         */
        if (erase == 'Y' || erase == 'y') {
            //bookTitle[index] = "";
            strcpy(bookTitle[index], "");
            //isbn[index] = "";
            strcpy(isbn[index], "");
            //author[index] = "";
            strcpy(author[index], "");
            //publisher[index] = "";
            strcpy(publisher[index], "");
            //dateAdded[index] = "";
            strcpy(dateAdded[index], "");
            qtyOnHand[index] = 0;
            wholesale[index] = 0;
            retail[index] = 0;
            bookCounter--;
            cout << "\nThe book has been deleted" << endl;
        }
    }
}
