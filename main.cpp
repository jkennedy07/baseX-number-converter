/*
CPSC 2382 (Assembly) - Fall 2019 - Cetinsaya
Jason Kennedy
*/

#include<iostream>
#include<string>
using namespace std;

// Simple struct containing the user's number as a string, and its base
struct Number {
	string value;
	int base{ 10 };
};

// Function Declarations
Number baseConversion(Number, int);
bool verifyInput(int);
bool verifyNumber(Number);
Number userInput();

// MAIN
int main() {
	char exit{ '0' };
	int finalBase{ 10 };

	while (exit != 'q') {
		system("CLS");
		Number userNumber = userInput();
		do {
			cout << "Please input the base (2-16) you wish to convert to: ";
			cin >> finalBase;
		} while (!verifyInput(finalBase));

		// Confirms the conversion being done for the user
		cout << "\nConverting base " << userNumber.base << " with value " << userNumber.value
			<< " to base " << finalBase << " ... " << endl;

		userNumber = baseConversion(userNumber, finalBase); // Function call to calculate the final result

		cout << endl << "Your number converted to base " << userNumber.base << " is: " << userNumber.value; // output

		cout << "\n\nType q to quit, or c to convert another number.";
		cin >> exit;
	}

	cout << "\n\n\n";
	system("pause");
	return 0;
} // end main

// *** FUNCTION DEFINITIONS ***
// Base Conversion Function
Number baseConversion(Number input, int finalBase) {

	Number result;
	result.base = finalBase;
	int remainder;

	// the stoi() function reads a string as a number of a given base and 
	// returns a base 10 integer, which we can then input into a conversion algorithm
	int baseTenNumber{ stoi(input.value, nullptr, input.base) };

	// This conversion algorithm works by dividing the number we are converting by 
	// the target base, and inserting the remainder into our output string, and repeating
	while (baseTenNumber > 0) {
		remainder = baseTenNumber % finalBase;
		baseTenNumber /= finalBase;
		if (remainder <= 9)
		{
			result.value.insert(result.value.begin(),
				remainder + '0');  // '0' = 48 which aligns ascii table
		}
		else if (remainder > 9)
		{
			result.value.insert(result.value.begin(),
				((remainder - 10) + 'A')); // inserts letters for bases >10
		}
	}
	return result;
}

// Checking input for valid base range 2-16
bool verifyInput(int input) {
	if (input > 16 || input < 2) {
		cout << "\nInvalid base. Please input a base in the range 2 to 16.";
		return false;
	}
	else
		return true;
}

// Checking for invalid numerals in user inputted number (e.g. 3 in a base 2 number)
bool verifyNumber(Number input) {
	if (!verifyInput(input.base)) {
		return false;
	}
	if (input.base <= 10) {
		for (auto& i : input.value) {
			if (i > input.base + '0' || i < '0') {
				cout << "\nError: entry contains incorrect digits/characters.";
				return false;
			}
		}
	}
	else if (input.base > 10) {
		for (auto& i : input.value) {
			// checks all invalid ranges 
			if ((i < '0')
				||
				(i > '9' && i < 'A')
				||
				((i > 'A' + input.base - 9) && (i < 'a'))
				||
				(i > 'a' + input.base - 9)) {
				cout << "\nError: entry contains invalid digits/characters.";
				return false;
			}
		}
	}
	return true;
}

// Receives input from user
Number userInput() {
	Number input;
	do {
		cout << "\nPlease input the base (2-16) of your number: ";
		cin >> input.base;
	} while (!verifyInput(input.base));
	do {
		cout << "\nPlease input the number you wish to convert: ";
		cin >> input.value;
	} while (!verifyNumber(input));
	return input;
}