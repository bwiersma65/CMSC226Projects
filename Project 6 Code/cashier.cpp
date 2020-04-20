//
//  cashier.cpp
//  Semester Project
//
//  Created by Ben Wiersma on 3/09/20.
//  Copyright © 2020 Ben Wiersma. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
// header files
#include "cashier.h"
#include "bookinfo.h"
using namespace std;

/*
Global arrays for holding data on each book
*/

extern char bookTitle[NUM_OF_ITEMS][TITLE_LENGTH], isbn[NUM_OF_ITEMS][ISBN_LENGTH], author[NUM_OF_ITEMS][31], publisher[NUM_OF_ITEMS][31], dateAdded[NUM_OF_ITEMS][DATE_LENGTH];
extern int qtyOnHand[NUM_OF_ITEMS];
extern double wholesale[NUM_OF_ITEMS], retail[NUM_OF_ITEMS];
extern int bookCounter;

void printMenu(char[], int, int[], char[NUM_OF_ITEMS][ISBN_LENGTH], char[NUM_OF_ITEMS][TITLE_LENGTH], float[], float[], float, float, float);

int cashier()
{
    cin.ignore();
    char proceed = 'y';
    const double TAX_RATE = 0.06;
    
    do {
        /*
         Arrays representing shopping cart
         */
        char cartTitle[NUM_OF_ITEMS][TITLE_LENGTH], cartISBN[NUM_OF_ITEMS][ISBN_LENGTH];
        int cartQTY[NUM_OF_ITEMS];
        float cartUnitPrice[NUM_OF_ITEMS], cartMerchTotal[NUM_OF_ITEMS];
        int cartIndex = -1;
        
        char isbnNum[ISBN_LENGTH], date[DATE_LENGTH];
        char bookProceed = 'y';
        float subTotal = 0.00, salesTax = 0.00, salesTotal = 0;
        
        
        cout << "\n////////////////////////////////////////////////////////////////////////////";
        cout << "\nSerendipity Book Sellers" << endl;
        cout << "\tCashier Module" << endl;
        cout << "\n\tDate: ";
        cin >> date;
        
        /*
         Book retrieval (one-at-a-time)
         */
        do {
            cin.ignore();
            int index = -1;
            int qtyDesired = 0;
            
            cout << "\n////////////////////////////////////////////////////////////////////////////";
            cout << "\nSerendipity Book Sellers" << endl;
            cout << "\tCashier Module" << endl;
            cout << "\n\tISBN: ";
            cin.getline(isbnNum, ISBN_LENGTH);
            cout << "\n\tQuantity Desired: ";
            cin >> qtyDesired;
            
            /*
             Searches array for book with given ISBN
             */
            for (int i = 0; i < bookCounter; i++) {
                if (strcmp(isbn[i], isbnNum) == 0) {
                    index = i;
                    break;
                }
            }
            
            /*
             If ISBN cannot be found, ask user if they would like to enter another number
                1. If yes, continue to next iteration of loop
                2. If no, end cashier function, returning to main menu
             */
            char mistakeProceed = 'y';
            if (index == -1) {
                cout << "Book with given ISBN could not be found" << endl;
                cout << "Would you like to enter another ISBN? (Y/N): " << endl;
                cin >> mistakeProceed;
                
                if (mistakeProceed == 'y' || mistakeProceed == 'Y')
                    continue;
                else
                    return 0;
            }
            
            cout << "\n\tFound It!" << endl;
            
            
            bookInfo(isbn[index], bookTitle[index], author[index], publisher[index], dateAdded[index], qtyOnHand[index], wholesale[index], retail[index]);
            
            /*
             Checks quantity to ensure order can be met
             */
            char goBack = 'z';
            if (qtyDesired > qtyOnHand[index]) {
                cout << "Sorry, there aren't copies of that book on hand to meet your order" << endl;
                cout << "Please enter \"Y\" to return to the main menu, where you may start over: ";
                cin >> goBack;
                while (goBack != 'Y' || goBack != 'y')
                {
                    cout << "Please enter \"Y\": ";
                    cin >> goBack;
                }
                return 0;
            }
            else {
                qtyOnHand[index] = (qtyOnHand[index] - qtyDesired);
            }
            
            
            cartIndex++;
            
            /*
             Stores book data into cart arrays
             */
            //cartTitle[cartIndex] = bookTitle[index];
            strcpy(cartTitle[cartIndex], bookTitle[index]);
            //cartISBN[cartIndex] = isbn[index];
            strcpy(cartISBN[cartIndex], isbn[index]);
            cartQTY[cartIndex] = qtyDesired;
            cartUnitPrice[cartIndex] = retail[index];
            cartMerchTotal[cartIndex] = (cartQTY[cartIndex] * cartUnitPrice[cartIndex]);
            
            
            subTotal += cartMerchTotal[cartIndex];
            

            cout << "\n\tWould you like to add another book to your cart?(Y/N): ";
            cin >> bookProceed;
        }
        
        /*
         Will loop asking for another book as long as:
            - user answers yes
            - cart size is less than cart capacity
         */
        while((bookProceed == 'y' || bookProceed == 'Y') && (cartIndex < NUM_OF_ITEMS));
        
        /*
         If this point reached, either:
            - user indicated done adding to cart
            - cart is full
         */
        
        salesTax = (TAX_RATE) * subTotal;
        
        salesTotal = subTotal + salesTax;
        
        printMenu(date, cartIndex, cartQTY, cartISBN, cartTitle, cartUnitPrice, cartMerchTotal, subTotal, salesTax, salesTotal);
            
        cout << "\nWould you like to perform another transaction?: ";
        cin >> proceed;
    }
    while (proceed == 'y' || proceed == 'Y');
    
    return 0;
}

/*
 Prints result of completed transaction to screen
 */
void printMenu(char date[], int cartIndex, int qty[], char isbn[NUM_OF_ITEMS][ISBN_LENGTH], char title[NUM_OF_ITEMS][TITLE_LENGTH], float unitPrice[], float merchTotal[], float subTotal, float salesTax, float salesTotal)
{
        cout << "\n////////////////////////////////////////////////////////////////////////////";
        cout << "\nSerendipity Book Sellers" << endl;
        cout << "\nDate: " << date << endl << endl;
        
        cout << left << "Qty " << setw(15) << "ISBN" << setw(40) << "Title" << setw(8) << "Price" << "Total" << endl;
        
        cout << "--------------------------------------------------------------------------" << endl;
    
        for (int i = 0; i <= cartIndex; i++) {
            cout << left << setw(4) << qty[i] << "" << setw(15) << isbn[i] << "" << setw(40) << title[i] << "$ " << setw(6) << setprecision(2) << fixed << showpoint << unitPrice[i] << "$ " << merchTotal[i] << endl;
        }
        
        cout << left << "\n\n\t\t" << setw(44) << "Subtotal" << "$ " << setw(6) << setprecision(2) << fixed << showpoint << subTotal << endl;
        cout << "\t\t" << setw(44) << "Tax" << "$ " << setw(6) << setprecision(2) << fixed << showpoint << salesTax << endl;
        cout << "\t\t" << setw(44) << "Total" << "$ " << setw(6) << setprecision(2) << fixed << showpoint << salesTotal << endl;
        cout << "\nThank You for Shopping at Serendipity!" << endl;
}
