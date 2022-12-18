/*
File: Problem1.cpp
Created by: Julia Troni
Creation Date: 1/20/2020
Synopsis: Program reads up to 100 numbers from a file and inserts them into an array in descending order
*/


#include <iostream>
#include <fstream>

using namespace std;


//insertIntoSortedArray() returns the current array size
int insertIntoSortedArray(float myArray[], int numEntries, float newValue);


int main (int argc, char const *argv[])
{
const int maxSize = 100;
float arr[maxSize];
float number;
int numEntries = 0;
string stuff;

ifstream theFile(argv[1]);  //opening file for reading

//checking that the file is open
if (!(theFile.is_open()))
{
    cout << "Failed to open the file." << endl;
}


//loop to read each element from the 
while (theFile.good())
{ 
    //reading integers from file
    getline(theFile, stuff); 
    number= stof(stuff);
    
    numEntries= insertIntoSortedArray(arr, numEntries, number);     //storing integers into sorted array
    
    //printing out entire array
    for (int i=0; i<numEntries; i++)
    {
        cout << arr[i];
        
        if (i<numEntries-1)
        {cout<< ", " ;}
    
    }
    cout <<endl;

}

 
return 0;

}

//insertIntoSortedArray() returns the current array size
int insertIntoSortedArray(float myArray[], int numEntries, float newValue)
{
int j;

//loop to find pivot point 
for (j= numEntries; j!= 0 && myArray[j-1] <= newValue; j--)
{
    myArray[j]=myArray[j-1];
}

//inserting new value into pivot point of the array
myArray[j]= newValue;

numEntries= numEntries + 1;


    return numEntries;
}