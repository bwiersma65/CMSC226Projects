//
//  cashier.h
//  Semester Project
//
//  Created by Ben Wiersma on 2/23/20.
//  Copyright © 2020 Ben Wiersma. All rights reserved.
//

#ifndef cashier_h
#define cashier_h

#include <string>
using namespace std;

const int NUM_OF_ITEMS = 20;
const int ISBN_LENGTH = 14, TITLE_LENGTH = 51, DATE_LENGTH = 11;

int cashier();
void printMenu(char[], int, int[], char[NUM_OF_ITEMS][ISBN_LENGTH], char[NUM_OF_ITEMS][TITLE_LENGTH], float[], float[], float, float, float);

#endif /* cashier_h */
