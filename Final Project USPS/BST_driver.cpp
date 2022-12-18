/**CPPFile*********************************************************************
   FileName    [BST_driver.cpp] 
   
   PackageName [none]

   Synopsis    [Implementation of Binary Search Tree]

   Description [File to read in 40,000 data values from a file and store them in an array.
                Then calculates the time to insert each set of 100 elements into a BST. Lastly 
                calculates the time it takes to search for 100 random ordered elements in the BST.]   

   SeeAlso     [BST.cpp, BST.hpp
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
/* Preprocessor directives                                                    */
/*---------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>


#include "BST.hpp"

/*---------------------------------------------------------------------------*/
/* Namespace declarations                                                    */
/*---------------------------------------------------------------------------*/
using namespace std;
using namespace chrono;

/*---------------------------------------------------------------------------*/
/* Global Declarations                                                       */
/*---------------------------------------------------------------------------*/

// Turn on or off to run the experiment for each data structure 
#define Binary_Search_Tree true


int main(int argc, char *argv[])
{
	ifstream dataFile;
    string dataString;

    const int DATA_SIZE=40000;
    int testData[DATA_SIZE];    //integer array to store the 40,000 elements from the data files
    float time_insert[400]; //array to hold time measurements for insertion 
    float time_search[400]; //array to hold time measurements for search 


    //error message if invalid arguments
	if (argc != 4)
	{
		cerr << "Invalid arguments, enter in format: ./a.out dataFileName.csv outputFileName1.csv outputFileName2" << endl;
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

    
#if Binary_Search_Tree

    BST tree;
    ofstream BSTinsertfile, BSTsearchfile; 

    high_resolution_clock::time_point insert_start, insert_end, search_start, search_end;
    duration<double> execTime;

    //opening files for writing
    BSTinsertfile.open(argv[2]); 
    BSTsearchfile.open(argv[3]);


    //error message if output file does not open 
	if (!BSTinsertfile.is_open())
	{
		cerr << "Could not open " << argv[2] << " for writing!" << endl;
		return 3;
	}
    if (!BSTsearchfile.is_open())
	{
		cerr << "Could not open " << argv[3] << " for writing!" << endl;
		return 4;
	}


    /****
     * INSERTION
     * 
    */ 
    for (int m=0; m<400; m++) 
    {

        for (int i=0; i<100; i++) 
        {
            insert_start = high_resolution_clock::now(); //starting the timer for insertion

            tree.addNode(testData[100*m+i]);  //inserting 100 elements at a time 

            insert_end = high_resolution_clock::now(); //stop the time for insertion
            execTime = execTime+ duration_cast<microseconds>(insert_end - insert_start);  //adding up the insertion time for each element to get the execution time for 100 elements 

        }

    
        time_insert[m]= execTime.count()/100; //getting average insertion time and storing into array
        BSTinsertfile << time_insert[m] << endl;   //writing average insertion time to file 

    }
    
    /****
     * SEARCH
     * 
    */ 
    for (int m=0; m<400; m++)
    {
      
        int randoIndices[100]; 
        for (int i = 0; i < 100; i++)  //populating array with 100 random index values with a range that corresponds to the iteration
        {
            randoIndices[i] = rand() % 100*m+100;   
        }

    
        for (int i=0; i<100; i++)
        {
            search_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to search
        
            tree.searchKey(testData[randoIndices[i]]); //searching the BST for data values that are in our BST somewhere
            
            search_end = high_resolution_clock::now(); //stop the time for the search opperation 
            execTime = execTime + duration_cast<microseconds>(search_end - search_start);  //summing the search time of each individual element to get the total search time for 100 elements

        
        }

        
        time_search[m]= execTime.count()/100; //storing average search time into an array
        BSTsearchfile << time_search[m] << endl;   //writing the search time to the file 

    }

    //closing the files
    BSTinsertfile.close(); 
    BSTsearchfile.close();

#endif


    dataFile.close(); 
}
