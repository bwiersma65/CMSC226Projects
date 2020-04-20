//
//  mainmenu.cpp
//  Semester Project
//
//  Created by Ben Wiersma on 2/10/20.
//  Copyright © 2020 Ben Wiersma. All rights reserved.
//

#include <iostream>
#include <string>
// header files for other functions
#include "cashier.h"
#include "invmenu.h"
#include "bookinfo.h"
#include "reports.h"
using namespace std;

/*
Global arrays for holding data on each book
*/
char bookTitle[NUM_OF_ITEMS][51], isbn[NUM_OF_ITEMS][14], author[NUM_OF_ITEMS]{31}, publisher[NUM_OF_ITEMS][31], dateAdded[NUM_OF_ITEMS][11];
int qtyOnHand[NUM_OF_ITEMS];
double wholesale[NUM_OF_ITEMS], retail[NUM_OF_ITEMS];
int bookCounter = 0;

int main()
{
    int input = 0;
    
    // do-while loop to repeat menu until 4 is selected
    do {
        // Menu Screen
        cout << "\n////////////////////////////////////////////////////////////////////////////";
        cout << "\n\t\t\tSerendipity Booksellers\n\t\t\t       Main Menu" << endl;
        cout << "\n\t\t\t1.  Cashier Module" << endl;
        cout << "\t\t\t2.  Inventory Database Module" << endl;
        cout << "\t\t\t3.  Report Module" << endl;
        cout << "\t\t\t4.  Exit" << endl;
        cout << "\n\t\t\tEnter Your Choice: ";
        
        cin >> input;
        
        // Input validation
        while (input < 1 || 4 < input)
        {
            cout << "\n\t\t\tPlease enter a number in the range 1 - 4" << endl;
            cout << "\n\t\t\tEnter Your Choice: ";
            cin >> input;
        }
        
        switch (input)
        {
            case 1: cashier(); // calls fxn from cashier.cpp
                break;
            case 2: invMenu(); // calls fxn from invmenu.cpp
                break;
            case 3: reports(); // calls fxn from reports.cpp
                break;
            case 4: cout << "\n\t\t\tYou selected item 4\n";
        }
    }
    while (input != 4);
}
