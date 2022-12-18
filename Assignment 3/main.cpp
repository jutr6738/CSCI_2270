/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* Julia Troni                                                  */
/* Assignment 3                                                 */  
/* Zagrodzki Section 100                                        */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>

void displayMenu();  // declaration for main's helper-function

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
int optionChosen=1;

while (optionChosen > 0 && optionChosen <=5)
{

    displayMenu(); //displaying the menu for the first time and user will select an option
    cin >> optionChosen; 

        if (optionChosen == 1)
        {
            CountryNet.loadDefaultSetup();
            CountryNet.printPath();
        }
        else if (optionChosen == 2)
        {
            CountryNet.printPath();
        }
        else if (optionChosen == 3)
        {
            string name; 
            string message;

            cout << "Enter name of the country to receive the message:" << endl;
            cin.ignore();
            getline(cin, name);
            cout << "Enter the message to send:" << endl;
            getline(cin, message);
            cout << endl; 
            CountryNet.transmitMsg(name, message);
        }
        else if (optionChosen == 4)
        {
            string insert; 
            string previous;
            cout << "Enter a new country name:" << endl;
            cin.ignore();
            getline (cin,insert);
            cout << "Enter the previous country name (or First):" << endl;
            getline(cin, previous);

            while ( previous != "First" && CountryNet.searchNetwork(previous) == NULL)
            {
                cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                getline(cin, previous);
            } 

            CountryNet.insertCountry(CountryNet.searchNetwork(previous), insert);
            CountryNet.printPath();
        }
        
        else if (optionChosen == 5)
        {
            cout << "Quitting... cleaning up path:" << endl;
            CountryNet.printPath();
            break;
        }
}
        if (optionChosen > 5 || optionChosen <= 0) 
        {
            cout << "Invalid Input" << endl;
        }

    
    cout << "Goodbye!" <<endl;

    return 0;
}


/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

//function append() inserts an element into an array but if the array is full, it performs array doubling and returns true.
// str_arr is an array of strings to insert elements into, s is the new string to insert, numEntries keeps track of the number of elements inserted so far, arraySize stores current array size
bool append (string* &str_arr, string s, int &numEntries, int &arraySize)
{
    bool doubled= false; //returns true if array is doubled 

    if (numEntries == arraySize)     //perform array doubling 
    {
        arraySize= 2*arraySize;     //increasing size of the array
        string *newarray= new string[arraySize]; //dynamically allocating a string array with double the size

        for (int i=0; i<arraySize/2; i++)
        {
            newarray[i]= str_arr[i];    //copying contents of str_arr to newarray
        }

        delete [] str_arr;   //freeing the memory of str_arr
        str_arr= newarray;
        doubled = true;
    }

    str_arr[numEntries]= s;   //inserting the new string into the array
    numEntries= numEntries+1;

    return(doubled);

}
