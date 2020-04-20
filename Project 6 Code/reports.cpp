//
//  reports.cpp
//  Semester Project
//
//  Created by Ben Wiersma on 3/09/20.
//  Copyright © 2020 Ben Wiersma. All rights reserved.
//

#include <iostream>
#include <string>
// header file
#include "reports.h"
#include "bookinfo.h"
using namespace std;

/*
Global arrays for holding data on each book
*/
const int NUM_OF_ITEMS = 20;
const int TITLE_LENGTH = 51, ISBN_LENGTH = 14, DATE_LENGTH = 11;
extern char bookTitle[NUM_OF_ITEMS][TITLE_LENGTH], isbn[NUM_OF_ITEMS][ISBN_LENGTH], author[NUM_OF_ITEMS][31], publisher[NUM_OF_ITEMS][31], dateAdded[NUM_OF_ITEMS][DATE_LENGTH];
extern int qtyOnHand[NUM_OF_ITEMS];
extern double wholesale[NUM_OF_ITEMS], retail[NUM_OF_ITEMS];
extern int bookCounter;

int reports()
{
    int input = 0;
    
    do {
        // Menu Screen
        cout << "\n////////////////////////////////////////////////////////////////////////////";
        cout << "\n\t\t\tSerendipity Booksellers\n\t\t\t\t\tReports" << endl;
        cout << "\n\t\t\t1.  Inventory Listing" << endl;
        cout << "\t\t\t2.  Inventory Wholesale Value" << endl;
        cout << "\t\t\t3.  Inventory Retail Value" << endl;
        cout << "\t\t\t4.  Listing by Quantity" << endl;
        cout << "\t\t\t5.  Listing by Cost" << endl;
        cout << "\t\t\t6.  Listing by Age" << endl;
        cout << "\t\t\t7.  Return to Main Menu" << endl;
        cout << "\n\t\t\tEnter Your Choice: ";
        
        cin >> input;
        
        // Input Validation
        while (input < 1 || 7 < input)
        {
            cout << "\n\t\t\tPlease enter a number in the range 1 - 7" << endl;
            cout << "\n\t\t\tEnter Your Choice: ";
            cin >> input;
        }
        
        switch (input)
        {
            case 1: repListing();
                break;
            case 2: repWholesale();
                break;
            case 3: repRetail();
                break;
            case 4: repQty();
                break;
            case 5: repCost();
                break;
            case 6: repAge();
                break;
            case 7: cout << "\n\t\t\tYou selected item 7\n";
        }
    }
    while (input != 7);
    return 0;
}

/**
 Prints list of all books currently in database
 */
void repListing()
{
    cin.ignore();
    int index = 0;
    char garbage[6];
    
    cout << "\n\t\t\tYou selected General Listing" << endl;
    
    while (index < bookCounter) {
        cout << "******************************************************" << endl;
        cout << "\nTitle: " << bookTitle[index] << endl;
        cout << "ISBN: " << isbn[index] << endl;
        cout << "Author: " << author[index] << endl;
        cout << "Publisher: " << publisher[index] << endl;
        cout << "Date Added to Our Inventory: " << dateAdded[index] << endl;
        cout << "Quantity on Hand: " << qtyOnHand[index] << endl;
        cout << "Wholesale Cost: " << wholesale[index] << endl;
        cout << "Retail Price: " << retail[index] << endl;
        index++;
        cout << "\nPress ENTER to continue to next listing: ";
        cin >> garbage;
    }
}

/**
 Prints listing of
    1. Title
    2. ISBN
    3. Quantity
    4. Wholesale Cost
 for each book in database, as well as total wholesale value of inventory
 */
void repWholesale()
{
    cin.ignore();
    int index = 0;
    char garbage[6];
    double wholeTotal = 0;
    
    cout << "\n\t\t\tYou selected Wholesale Listing" << endl;
    
    while (index < bookCounter) {
        cout << "******************************************************" << endl;
        cout << "\nTitle: " << bookTitle[index] << endl;
        cout << "ISBN: " << isbn[index] << endl;
        cout << "Quantity on Hand: " << qtyOnHand[index] << endl;
        cout << "Wholesale Cost: " << wholesale[index] << endl;
        
        wholeTotal = wholeTotal + (qtyOnHand[index] * wholesale[index]);
        index++;
        
        cout << "\nPress ENTER to continue to next listing: ";
        cin >> garbage;
    }
    
    cout << "\nTotal Wholesale Value of Inventory: " << wholeTotal << endl;
}

/**
 Prints listing of
    1. Title
    2. ISBN
    3. Quantity on Hand
    4. Retail Price
 for each book in database, as well as total retail value of inventory
 */
void repRetail()
{
    cin.ignore();
    int index = 0;
    char garbage[6];
    double retailTotal = 0.0;
    
    cout << "\n\t\t\tYou selected Retail Listing" << endl;
    
    while (index < bookCounter) {
        cout << "******************************************************" << endl;
        cout << "\nTitle: " << bookTitle[index] << endl;
        cout << "ISBN: " << isbn[index] << endl;
        cout << "Quantity on Hand: " << qtyOnHand[index] << endl;
        cout << "Retail Price: " << retail[index] << endl;
        
        retailTotal += (retail[index] * qtyOnHand[index]);
        index++;
        
        cout << "\nPress ENTER to continue to next listing: ";
        cin >> garbage;
    }
    
    cout << "\nTotal Retail Value of Inventory: " << retailTotal << endl;
}

/**
Prints list of all books in inventory (plus accompanying data) sorted according to quantity (from greatest to least)
*/
void repQty()
{
    //string descendingTitle[bookCounter], descendingISBN[bookCounter];
    char descendingTitle[bookCounter][TITLE_LENGTH], descendingISBN[bookCounter][ISBN_LENGTH];
    //string titleTemp, isbnTemp, garbage;
    char titleTemp[TITLE_LENGTH], isbnTEMP[ISBN_LENGTH], garbage[6];
    int descendingQty[bookCounter];
    int maxVal, maxIndex, qtyTemp, index = 0;;
    
    /*
     Copies of global arrays
     */
    for (int i = 0; i < bookCounter; i++) {
        //descendingTitle[i] = bookTitle[i];
        strcpy(descendingTitle[i], bookTitle[i]);
        //descendingISBN[i] = isbn[i];
        strcpy(descendingISBN[i], isbn[i]);
        descendingQty[i] = qtyOnHand[i];
    }
    
    cin.ignore();
    cout << "\n\t\t\tYou selected Listing By Quantity" << endl;
    
    /*
     Selection sort
     */
    for (int i = 0; i < (bookCounter - 1); i++) {
        
        maxVal = descendingQty[i];
        maxIndex = i;
        for (int j = (i + 1); j < bookCounter; j++) {
            if (descendingQty[j] > maxVal)
            {
                maxVal = descendingQty[j];
                maxIndex = j;
            }
        }
        qtyTemp = descendingQty[maxIndex];
        descendingQty[maxIndex] = descendingQty[i];
        descendingQty[i] = qtyTemp;
        
        //titleTemp = descendingTitle[maxIndex];
        strcpy(titleTemp, descendingTitle[maxIndex]);
        //descendingTitle[maxIndex] = descendingTitle[i];
        strcpy(descendingTitle[maxIndex], descendingTitle[i]);
        //descendingTitle[i] = titleTemp;
        strcpy(descendingTitle[i], titleTemp);
        
        //isbnTemp = descendingISBN[maxIndex];
        strcpy(isbnTEMP, descendingISBN[maxIndex]);
        //descendingISBN[maxIndex] = descendingISBN[i];
        strcpy(descendingISBN[maxIndex], descendingISBN[i]);
        //descendingISBN[i] = isbnTemp;
        strcpy(descendingISBN[i], isbnTEMP);
    }
    
    while (index < bookCounter) {
        cout << "******************************************************" << endl;
        cout << "\nTitle: " << descendingTitle[index] << endl;
        cout << "ISBN: " << descendingISBN[index] << endl;
        cout << "Quantity on Hand: " << descendingQty[index] << endl;
        
        index++;
        
        cout << "\nPress ENTER to continue to next listing: ";
        cin >> garbage;
    }
}

/**
Prints list of all books in inventory (plus accompanying data) sorted according to wholesale cost (from greatest to least)
*/
void repCost()
{
    //string descendingTitle[bookCounter], descendingISBN[bookCounter];
    char descendingTitle[bookCounter][TITLE_LENGTH], descendingISBN[bookCounter][ISBN_LENGTH];
    //string titleTemp, isbnTemp, garbage;
    char titleTemp[TITLE_LENGTH], isbnTemp[ISBN_LENGTH], garbage[6];
    int descendingQty[bookCounter];
    int maxIndex, qtyTemp, index = 0;
    double descendingWholesale[bookCounter];
    double maxVal, wholesaleTemp;
    
    /*
     Copies of global arrays
     */
    for (int i = 0; i < bookCounter; i++) {
        //descendingTitle[i] = bookTitle[i];
        strcpy(descendingTitle[i], bookTitle[i]);
        //descendingISBN[i] = isbn[i];
        strcpy(descendingISBN[i], isbn[i]);
        descendingQty[i] = qtyOnHand[i];
        descendingWholesale[i] = wholesale[i];
    }
    
    cin.ignore();
    cout << "\n\t\t\tYou selected Listing By Cost" << endl;
    
    /*
     Selection sort
     */
    for (int i = 0; i < (bookCounter - 1); i++) {
        
        maxVal = descendingWholesale[i];
        maxIndex = i;
        for (int j = (i + 1); j < bookCounter; j++) {
            if (descendingWholesale[j] > maxVal)
            {
                maxVal = descendingWholesale[j];
                maxIndex = j;
            }
        }
        wholesaleTemp = descendingWholesale[maxIndex];
        descendingWholesale[maxIndex] = descendingWholesale[i];
        descendingWholesale[i] = wholesaleTemp;
        
        //titleTemp = descendingTitle[maxIndex];
        strcpy(titleTemp, descendingTitle[maxIndex]);
        //descendingTitle[maxIndex] = descendingTitle[i];
        strcpy(descendingTitle[maxIndex], descendingTitle[i]);
        //descendingTitle[i] = titleTemp;
        strcpy(descendingTitle[i], titleTemp);
        
        //isbnTemp = descendingISBN[maxIndex];
        strcpy(isbnTemp, descendingISBN[maxIndex]);
        //descendingISBN[maxIndex] = descendingISBN[i];
        strcpy(descendingISBN[maxIndex], descendingISBN[i]);
        //descendingISBN[i] = isbnTemp;
        strcpy(descendingISBN[i], isbnTemp);
        
        qtyTemp = descendingQty[maxIndex];
        descendingQty[maxIndex] = descendingQty[i];
        descendingQty[i] = qtyTemp;
    }
    
    while (index < bookCounter) {
        cout << "******************************************************" << endl;
        cout << "\nTitle: " << descendingTitle[index] << endl;
        cout << "ISBN: " << descendingISBN[index] << endl;
        cout << "Quantity on Hand: " << descendingQty[index] << endl;
        cout << "Wholesale Cost: " << descendingWholesale[index] << endl;
        
        index++;
        
        cout << "\nPress ENTER to continue to next listing: ";
        cin >> garbage;
    }
}

/**
Prints list of all books in inventory (plus accompanying data) sorted according to date added to inventory (from earliest to most recent)
*/
void repAge()
{
    //string descendingTitle[bookCounter], descendingISBN[bookCounter], descendingDate[bookCounter];
    char descendingTitle[bookCounter][TITLE_LENGTH], descendingISBN[bookCounter][ISBN_LENGTH], descendingDate[bookCounter][DATE_LENGTH];
    //string minDate, YYYY, MM, DD, testYYYY, testMM, testDD, titleTemp, isbnTemp, dateTemp, garbage;
    char minDate[DATE_LENGTH], YYYY[5], MM[3], DD[3], testYYYY[5], testMM[3], testDD[3], titleTemp[TITLE_LENGTH], isbnTemp[ISBN_LENGTH], dateTemp[DATE_LENGTH], garbage[6];
    int descendingQty[bookCounter];
    int minIndex, qtyTemp, index = 0;
    
    /*
     Copies of global arrays
     */
    for (int i = 0; i < bookCounter; i++) {
        //descendingTitle[i] = bookTitle[i];
        strcpy(descendingTitle[i], bookTitle[i]);
        //descendingISBN[i] = isbn[i];
        strcpy(descendingISBN[i], isbn[i]);
        //descendingDate[i] = dateAdded[i];
        strcpy(descendingDate[i], dateAdded[i]);
        descendingQty[i] = qtyOnHand[i];
    }
    
    cin.ignore();
    cout << "\n\t\t\tYou selected Listing By Age" << endl;
    
    /*
     Selection sort
     */
    for (int i = 0; i < (bookCounter - 1); i++) {
        
        //minDate = descendingDate[i];
        strcpy(minDate, descendingDate[i]);
        minIndex = i;
        for (int j = (i + 1); j < bookCounter; j++) {
            //string YYYY(minDate, 6, 4);
            int index = 0;
            for (int i = 6; i < 10; i++, index++)
                YYYY[index] = minDate[i];
            //string testYYYY(descendingDate[j], 6, 4);
            index = 0;
            for (i = 6; i < 10; i++, index++)
                testYYYY[index] = descendingDate[j][i];
            //if (YYYY > testYYYY)
            if (strcmp(YYYY, testYYYY) > 0)
            {
                //minDate = descendingDate[j];
                strcpy(minDate, descendingDate[j]);
                minIndex = j;
            }
            //else if (YYYY == testYYYY)
            else if (strcmp(YYYY, testYYYY) == 0)
            {
                //string MM(minDate, 0, 2);
                for (i = 0; i < 2; i++)
                    MM[i] = minDate[i];
                //string testMM(descendingDate[j], 0, 2);
                for (i = 0; i < 2; i++)
                    testMM[i] = descendingDate[j][i];
                //if (MM > testMM)
                if (strcmp(MM, testMM) > 0)
                {
                    //minDate = descendingDate[j];
                    strcpy(minDate, descendingDate[j]);
                    minIndex = j;
                }
                //else if (MM == testMM)
                else if (strcmp(MM, testMM) == 0)
                {
                    //string DD(minDate, 3, 2);
                    index = 3;
                    for (i = 0; i < 2; i++, index++)
                        DD[i] = minDate[index];
                    //string testDD(descendingDate[j], 3, 2);
                    index = 3;
                    for (i = 0; i < 2; i++, index++)
                        testDD[i] = descendingDate[j][index];
                    //if (DD > testDD)
                    if (strcmp(DD, testDD) > 0)
                    {
                        //minDate = descendingDate[j];
                        strcpy(minDate, descendingDate[j]);
                        minIndex = j;
                    }
                }
            }
        }
        //dateTemp = descendingDate[minIndex];
        strcpy(dateTemp, descendingDate[minIndex]);
        //descendingDate[minIndex] = descendingDate[i];
        strcpy(descendingDate[minIndex], descendingDate[i]);
        //descendingDate[i] = dateTemp;
        strcpy(descendingDate[i], dateTemp);
        
        //titleTemp = descendingTitle[minIndex];
        strcpy(titleTemp, descendingTitle[minIndex]);
        //descendingTitle[minIndex] = descendingTitle[i];
        strcpy(descendingTitle[minIndex], descendingTitle[i]);
        //descendingTitle[i] = titleTemp;
        strcpy(descendingTitle[i], titleTemp);
        
        //isbnTemp = descendingISBN[minIndex];
        strcpy(isbnTemp, descendingISBN[minIndex]);
        //descendingISBN[minIndex] = descendingISBN[i];
        strcpy(descendingISBN[minIndex], descendingISBN[i]);
        //descendingISBN[i] = isbnTemp;
        strcpy(descendingISBN[i], isbnTemp);
        
        qtyTemp = descendingQty[minIndex];
        descendingQty[minIndex] = descendingQty[i];
        descendingQty[i] = qtyTemp;
    }
    
    while (index < bookCounter) {
        cout << "******************************************************" << endl;
        cout << "\nTitle: " << descendingTitle[index] << endl;
        cout << "ISBN: " << descendingISBN[index] << endl;
        cout << "Quantity on Hand: " << descendingQty[index] << endl;
        cout << "Date Added: " << descendingDate[index] << endl;
        
        index++;
        
        cout << "\nPress ENTER to continue to next listing: ";
        cin >> garbage;
    }
}
