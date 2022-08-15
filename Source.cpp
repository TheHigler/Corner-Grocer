/*Ron Bal
CS-210 Programming Languages
Corner Grocer Module 7 project*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <cstring>
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
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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


void Menu() {
	/*
	Print function to create a menu of selections for user.
	Need to print all purchased items, total amount for specific item, display a histogram,
	and exit the program.
	Do/while until user exits program
	Try/catch to handle valid/invalid input from user
	*/

	bool programRun = true;  //Bool true while program runs, false to end program
	bool correctInput;
	int userChoice;          //Get input for menu choice
	string groceryType;      //Get input for grocery item to be searched for

	do {

		cout << endl;
		cout << "******************************************************************************" << endl;
		cout << "***                       Please Select an option                          ***" << endl;
		cout << "******************************************************************************" << endl;
		cout << endl;
		cout << "******************************************************************************" << endl;
		cout << "***   1. Print List of All Purchased Items and How Many Were Purchased     ***" << endl;
		cout << "***   2. Print Total Amount Purchased of a Specific Item                   ***" << endl;
		cout << "***   3. Display Text Histogram                                            ***" << endl;
		cout << "***   4. Exit The Program                                                  ***" << endl;
		cout << "******************************************************************************" << endl;
		cout << endl;

		try {
			std::cin >> userChoice;
			cout << "******************************************************************************" << endl;
			cout << endl;
			
			while (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Unknown Entry. Please Try Again." << endl;

				cout << "Please enter only 1, 2, 3, or 4." << endl;
				std::cin >> userChoice;
				cout << "******************************************************************************" << endl;
				cout << endl;
			}
			if (userChoice >= 0) { 
				//Passes try test, checks for valid input, and exits do/while loop
				correctInput = true;
			}
			else { throw (userChoice); }
		}
		catch (...) { cout << "Please Enter only 1, 2, 3, or 4." << endl; } //Catch if input is not an integer


		if (userChoice == 1) {

			system("Color 05");
			//Prints the total amount of products purchased that day stored in a file

			cout << endl;
			cout << "##############################################################################" << endl;
			cout << "#                         Total Produce Purchased Today                      #" << endl;
			cout << "##############################################################################" << endl;
			cout << endl;

			CallProcedure("read_File"); //Read file in python

		}
		else if (userChoice == 2) {

			system("Color 01");
			//Ask user which product to be looked up, call Python funtion for frequency

			string userString;
			cout << "Please Enter the Product you would like to look up: ";
			std::cin >> userString; //Gets product user requested

			int tot = callIntFunc("locate_Total_Product_Amount", userString); //Gets frequency of chosen product

			if (tot == -1) {
				cout << "The item could not be located within the data file. Make sure input is correct." << endl; //Message to user if product not in list, check for spelling.
			}
			else {
				cout << "There were a total of " << tot << " " << userString << " sold today." << endl; //Print how many of user requested item sold today
			}
		}
		else if (userChoice == 3) {
			system("Color 03");

			/*Calls Python function to read file, countand sort product amounts
			  Write to .dat file
			  Rread .dat file and create a histogram*/

			CallProcedure("read_AND_Write_File");

		}
		else { programRun = false; } // End Program

	} while (programRun == true); //controls program flow
}



int main() {
	system("Color 01");

	//Call menu funtion
	Menu();

	//Message when user exits program
	cout << endl;
	cout << "******************************************************************************" << endl;
	cout << "***                      Program Shutting Down...                          ***" << endl;
	cout << "******************************************************************************" << endl;

	return 0;
}