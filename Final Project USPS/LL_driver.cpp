/**CPPFile*********************************************************************
   FileName    [LL_driver.cpp] 
   
   PackageName [none]

   Synopsis    [Implementation of Linked List]

   Description [File to read in 40,000 data values from a file and store them in an array.
                Then calculates the time to insert each set of 100 elements into a linked list at the head. 
                Lastly calculates the time it takes to search for 100 random ordered elements in the linked list.]   

   SeeAlso     [linkedlist.cpp, linkedlist.hpp
                Final Report for the full analysis of time complexity for linked list, binary search
                tree, and hash tables ]       

   Author      [Julia Troni (jutr6738@colorado.edu)]
   
   Copyright   [This program is free software; you can redistribute it and/or modify it
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
/* Preprocessor Directives                                                   */
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


   //insertion
    for (int m=0; m<400; m++)  
    {
        //Create a temp_time_variable
        for (int i=0; i<100; i++)       //inserting 100 elements at a time into the linked list
        {
            insert_start = high_resolution_clock::now(); //starting the timer

            LL.insert(NULL,testData[m*100+i]);  //inserting each element at the head 

            insert_end = high_resolution_clock::now(); //stop the time 
           
            execTime= execTime + duration_cast<microseconds>(insert_end - insert_start);  //adding the time difference

        }
        
        execTime=execTime/100;
        time_insert[m]= execTime.count();     //average insertion time 
       
        LLfileinsert << time_insert[m]  << endl;  //writing the average insertion time to the file
        
    }

    //search
    for (int m=0; m<400; m++)
    {
      
        int randoIndices[100]; 
        for (int i = 0; i < 100; i++)  //populating array with random values 
        {
            randoIndices[i] = rand() % 100*m+100;
        }

        
        for (int i=0; i<100; i++)
        {
            search_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to search
            LL.searchList(testData[randoIndices[i]]); //searching the linked list for 100 total data values but in a random order
            search_end = high_resolution_clock::now(); //stop the time for the search opperation

            execTime = execTime + duration_cast<microseconds>(search_end - search_start);  //the difference bw end and start is how long search of 100 elements took 
        }

         
        time_search[m]= execTime.count()/100; //storing average search time into an array
        LLfilesearch << time_search[m] << endl;   //writing the search time to the file 

    }

    LLfileinsert.close(); 
    LLfilesearch.close(); 
#endif 




    dataFile.close(); 
}