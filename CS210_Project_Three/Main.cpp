/*
CS-210 Project 3
Matthew Bandyk
Main file
V1 - 12/11/2022

This is the main file for the Grocery Tracking program. See inline comments for details throughout.
See Class Execution cpp file for details on functions called below.
*/

#include "Execution.h"
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_P3_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = NULL, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_P3_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_P3_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


int main() {
	Execution user;
	int menuChoice;
	int holder;
	string itemChoice;
	bool quit = false;

	system("Color 09"); // sets background and text color for the program

	while (!quit) { // Loops through the program until user selects 4 to quit
		user.DisplayMenu();
		menuChoice = user.UserInput(); // gets and validates user input from the menu

		// switch case to run correct option based on user input
		switch (menuChoice) {
		case 1: // displays all products sold and number of each product sold - Python code
			CallProcedure("ItemTotals"); 
			break;

		case 2: // captures user input for item to look up and collect total sold of that item
			cout << "What item would you like to look up? ";
			cin >> itemChoice;
			itemChoice[0] = toupper(itemChoice[0]);
			cout << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "Number of " << itemChoice << " sold this day: " << callIntFunc("SingleItem", itemChoice) << endl;
			cout << endl;
			break;

		case 3: // Displays a histogram of types of items sold and total sold of each
			CallProcedure("CreateDat"); // creates .dat file 
			user.DisplayHisto(); // displays histogram
			break;

		case 4: // User choice was to quit, displays exit screen and then ends program
			quit = true;
			cout << "-------------------------------------------------------" << endl;
			cout << "||             Now Exiting the Program               ||" << endl;
			cout << "||                Have a nice Day!                   ||" << endl;
			cout << "-------------------------------------------------------" << endl;
			Sleep(1000);
			break;
		}
	}
}