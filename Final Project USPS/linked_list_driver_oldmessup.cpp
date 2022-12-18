/**CPPFile*********************************************************************
   FileName    [linked_list_driver.cpp] 
   
   PackageName [none]

   Synopsis    [Implementation of linked list]

   Description []   

   SeeAlso     []       

   Author      [

   Julia Troni (jutr6738@colorado.edu)

   ]
   Copyright   [ 
   
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2 of the License, or (at your option) any
   later version.  
  
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details
   at http://www.gnu.org/copyleft/gpl.html
   
   ]

*******************************************************************************/

/*---------------------------------------------------------------------------*/
/* Library declarations                                                    */
/*---------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>


#include "linkedlist.hpp"

/*---------------------------------------------------------------------------*/
/* Namespace declarations                                                    */
/*---------------------------------------------------------------------------*/
using namespace std;
using namespace chrono;

/*---------------------------------------------------------------------------*/
/* Global Declarations                                                       */
/*---------------------------------------------------------------------------*/

// Turn on or off to run the experiment for each data structure 
#define LINKED_LIST true


int main(int argc, char *argv[])
{
	ifstream dataFile;
    string dataString;

    const int DATA_SIZE=40000;
    int testData[DATA_SIZE];    //integer array to store the 40,000 elements from the data files
    float time_insert[400]; //array to record the time measurements for 
    float time_search[400];


    //error message if invalid arguments
	if (argc != 4)
	{
		cerr << "Invalid arguments, enter in format: ./a.out dataFileName.csv outputFileName1.csv outputFileName2.csv" << endl;
		return 1;
	}

	dataFile.open(argv[1]);     //opening data file for reading

    //error message if data file does not open 
	if (!dataFile.is_open())
	{
		cerr << "Could not open " << argv[1] << " for reading!" << endl;
		return 2;
	}

    //reading in the data from the file 
    int i=0; 
	while (getline(dataFile, dataString, ','))
	{
        testData[i]=stoi(dataString); 
        i++; 
    }

    
#if LINKED_LIST
    LinkedList LL;
    ofstream LLfileinsert, LLfilesearch; 

    high_resolution_clock::time_point insert_start, insert_end, search_start, search_end;
    duration<double> execTime;


    LLfileinsert.open(argv[2]); 
    LLfilesearch.open(argv[3]);

    //error message if output file does not open 
	if (!LLfileinsert.is_open())
	{
		cerr << "Could not open " << argv[2] << " for writing!" << endl;
		return 3;
	}
    if (!LLfilesearch.is_open())
	{
		cerr << "Could not open " << argv[3] << " for writing!" << endl;
		return 4;
	}

    insert_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to insert

    LL.insert(NULL, testData[0]);   //inserting 1st element into linked list
    for (int i=1; i<100; i++)
    {
        int prevvalue= testData[i-1];
        LL.insert(LL.searchList(prevvalue),testData[i]);  
    }

    insert_end = high_resolution_clock::now(); //stop the time for the insertion opperation 
    execTime = duration_cast<microseconds>(insert_end - insert_start);  //the difference bw end and start is how long insertion of 100 elements took 

    time_insert[0]= execTime.count()/100; //getting average insertion time and storing into array
    LLfileinsert << time_insert[0] << endl;   //writing to file 

    cout << "Time to insert the first 100 elements into Linked List: " << execTime.count() << " seconds." << endl;
    cout << "Average insertion time in Linked List : " << time_insert[0] << " seconds." << endl;

/**
 * searching
 * 
*/

    int randoIndices[100]; 

    for (int i = 0; i < 100; i++)  //populating array with random values 
    {
        randoIndices[i] = rand() % 100;
    }

    search_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to search
    for (int i=0; i<100; i++)
    {
        LL.searchList(testData[randoIndices[i]]); //searching the linked list for each of the first 0-100 data values, but in a random order
    }
    search_end = high_resolution_clock::now(); //stop the time for the insertion opperation 
    execTime = duration_cast<microseconds>(search_end - search_start);  //the difference bw end and start is how long insertion of 100 elements took 

    time_search[0]= execTime.count()/100; //getting average insertion time and storing into array
    LLfilesearch << time_search[0] << endl;   //writing to file 

    cout << "Time to search the first 100 elements into Linked List: " << execTime.count() << " seconds." << endl;
    cout << "Average search time in Linked List : " << time_search[0] << " seconds." << endl;




    
    /****************************************************
    *****
    Repeating for next 3900 elements 
    ***********************************************
    */

   //insertion
    for (int m=2; m<=400; m++)  
    {
        insert_start = high_resolution_clock::now(); //starting the timer

        for (int i=1; i<100; i++)       //inserting 100 elements into the linked list
        {
            int prevvalue= testData[m*100+i-2];
            LL.insert(LL.searchList(prevvalue),testData[m*100+i-1]);
            
        }
        
        insert_end = high_resolution_clock::now(); //stop the time 
        execTime = duration_cast<microseconds>(insert_end - insert_start);  //how long the insertion took for 100 elements
        time_insert[m-1]= execTime.count()/100;     //average insertion time 
        LLfileinsert << time_insert[m-1] << endl;  //writing the average insertion time to the file
    }

    //search
    for (int m=2; m<=400; m++)
    {
      
        int randoIndices[m*100]; 
        for (int i = 0; i < 100*m; i++)  //populating array with random values 
        {
            randoIndices[i] = rand() % 100;
        }

        search_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to search
        for (int i=0; i<100; i++)
        {
            LL.searchList(testData[randoIndices[i]]); //searching the linked list for 100 total data values but in a random order
        }

        search_end = high_resolution_clock::now(); //stop the time for the search opperation 
        execTime = duration_cast<microseconds>(search_end - search_start);  //the difference bw end and start is how long search of 100 elements took 

        time_search[m-1]= execTime.count()/100; //storing average search time into an array
        LLfilesearch << time_search[m-1] << endl;   //writing the search time to the file 

    }

    LLfileinsert.close(); 
    LLfilesearch.close(); 
#endif 




    dataFile.close(); 
}