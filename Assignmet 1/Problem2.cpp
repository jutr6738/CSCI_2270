/*
File: Problem2.cpp
Created by: Julia Troni
Creation Date: 1/22/2020
Synopsis: Program reads up to 100 lines and columns from a .csv file containing information on national parks and stores the information in an array of structs. Then it writes the lines to the output .csv file where the area of the park is within a range specified by an upper and lower bound.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//declaration of the Park struct
struct Park{
    string parkname;
    string state;
    int area;
};

//declarion of the function addpark
void addPark (Park parks[], string parkname, string state, int area, int length);

//declaration of the fuction printList
void printList (const Park parks[], int length);

int main(int argc, char const *argv[])
{
    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    int MAXSIZE=100;
    Park parks[MAXSIZE];

    string line, name, state, tempstr;
    int area;
    int currentLength=0;

    //checking that the input file is open
    if (!inputFile.is_open())
    {
        cout << "Failed to open the input file." << endl;
    }
    //checking that the output file is open
    if (!outputFile.is_open())
    {
        cout << "Failed to open the output file." << endl;
    }

    //loop to read all of input file contents 
    while (inputFile.good())
    {


        //loop to read each line of the input file
        while (getline(inputFile,line))
        {
            stringstream ss(line); 
            
            //parsing each line to store appropiate data to appropiate variables
            getline (ss, name, ',');
            getline (ss, state, ',');
            getline (ss, tempstr, ',');
            area= stoi(tempstr);
            addPark (parks, name, state, area, currentLength); //adding the information to the parks array
            currentLength= currentLength + 1; 
            
        }


    

    }

    //printing out the elements of the park arrray
    printList(parks, currentLength);

    //writing to the output .csv file: writing the parkname, state, area of the parks with areas between the lower and upper bound

    for (int i=1; i<currentLength+1; i++)
    {
        if (parks[i].area >= (stoi(argv[3])) && parks[i].area<= (stoi(argv[4])))
        {
            outputFile << parks[i].parkname << "," << parks[i].state << "," << parks[i].area <<endl;
        }
    }  
  



    inputFile.close();  //closing the file
    outputFile.close(); 

    return 0;
}


//function addpark instantiates a array of structs and stores the parkname, state, and area in it
void addPark (Park parks[], string parkname, string state, int area, int length)
{
    parks[length].parkname= parkname;
    parks[length].state= state;
    parks[length].area=area;

}

//fuction printList prints each element of the parks array in the following format: PARKNAME [STATE] area: AREA
void printList (const Park parks[], int length)
{
    for (int i=0; i<length; i++)
    {
        cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area <<endl;
    }
}
