//
//  bookinfo.cpp
//  Semester Project
//
//  Created by Ben Wiersma on 2/10/20.
//  Copyright © 2020 Ben Wiersma. All rights reserved.
//

#include <iostream>
#include <cstring>
// header file
#include "bookinfo.h"
using namespace std;

void strUpper(char *);

/*
Global arrays for holding data on each book
*/
const int NUM_OF_ITEMS = 20;
extern char bookTitle[NUM_OF_ITEMS][51], isbn[NUM_OF_ITEMS][14], author[NUM_OF_ITEMS][31], publisher[NUM_OF_ITEMS][31], dateAdded[NUM_OF_ITEMS][11];
extern int qtyOnHand[NUM_OF_ITEMS];
extern double wholesale[NUM_OF_ITEMS], retail[NUM_OF_ITEMS];
extern int bookCounter;

/*
 Function displaying menu for bookInfo screen
 */
void bookInfo(char isbn[], char title[], char author[], char publisher[], char date[], int qty, double wholesale, double retail)
{
    // Menu Screen
    cout << "\n////////////////////////////////////////////////////////////////////////////";
    cout << "\n\t\t\tSerendipity Booksellers\n\t\t\t\tBook Information" << endl;
    cout << "\nISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Date Added: " << date << endl;
    cout << "Quantity-On-Hand: " << qty << endl;
    cout << "Wholesale Cost: " << wholesale << endl;
    cout << "Retail Price: " << retail << endl;
    
}

/*
 Accepts pointer to c-string
 Replaces each character with uppercase version
 */
void strUpper(char* name)
{
    while (isprint(*name)) {
        *name = toupper(*name);
        name++;
    }
}
