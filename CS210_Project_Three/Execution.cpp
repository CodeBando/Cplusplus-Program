/*
CS-210 Project 3
Matthew Bandyk
Class Execution cpp file
V1 - 12/11/2022

This is the Class Execution. This class houses all the functions for the class functions to display menu's, histograms and validate inputs.

Discriptions of each function can be found in the inline comments below.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "Execution.h"

using namespace std;

Execution::Execution() { // default constructor
}

void Execution::DisplayMenu() { // Function that displays the main menu for the program
	cout << "-------------------------------------------------------" << endl;
	cout << "||                   Corner Grocer                   ||" << endl;
	cout << "||               Item-Tracking Systems               ||" << endl;
	cout << "||---------------------------------------------------||" << endl;
	cout << "||                                                   ||" << endl;
	cout << "||                 *** Main Menu ***                 ||" << endl;
	cout << "||                                                   ||" << endl;
	cout << "||---------------------------------------------------||" << endl;
	cout << "||   1) - Display type and total of items sold       ||" << endl;
	cout << "||   2) - Find total of single item sold             ||" << endl;
	cout << "||   3) - Display text histogram of items sold       ||" << endl;
	cout << "||   4) - Exit the program                           ||" << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "Enter menu number to proceed (1, 2, 3, 4)" << endl;
}

int Execution::UserInput() { // Function to capture the user input for menu options, then run the function to validate it, then returns it
	int userInput;

	userInput = ValidateInput();

	return userInput;
}

int Execution::ValidateInput() { // Validates user input to ensure it is one of the menu options
	bool ok = false;
	bool cont = false;
	int x;

	while (!cont) {
		while (!ok) {
			ok = true;
			cin >> x;


			if (!cin) { // Validates user input
				ok = false;
				cin.clear();
				cin.ignore(500, '\n');
			}
			if (!ok) {
				cout << "Invalid input, please try again: \n";
			}
		}

		if ((x < 1) || (x > 4)) {
			cout << "Invalid input, please try again: \n";
			ok = false;
			cin.clear();
			cin.ignore(500, '\n');
		}

		else {
			cont = true;
		}

		cout << endl;
	}
	return x;
}

void Execution::DisplayHisto() { // Function that pulls data from dat file to create a histogram of all the purchased items and displays total sold as a symbol
	ifstream datFile;
	string item;
	int num;
	int i;
	char c = '$'; // char used to indicate a sold item

	datFile.open("frequency.dat"); // opens .dat file with products sold information

	cout << "-----------------------------------------------------------" << endl; // header for the display
	cout << "||  Histogram chart of all products sold and total sold  ||" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << endl;

	if (!datFile.is_open()) { // validates file has been opened
		cout << "Could not open the frequency.dat file" << endl;
	}

	else {
		datFile >> item >> num; // reads the first line of the file and assigns to item and num

		while (!datFile.fail()) { // loops through the file until the end of the file is reached

			cout << "  " << item << ": ";
			for (i = 1; i <= num; ++i) { // loops until char has been printed i times, based on number of that item sold
				cout << c;
			}
			cout << endl;
			cout << endl;

			datFile.ignore(); // ignore's \n at end of line

			datFile >> item >> num; // reads the next line of the file and assigns to item and num
		}
	}
	datFile.close();
}