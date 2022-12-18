#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>


#include "hash.hh"

/*---------------------------------------------------------------------------*/
//driver file for hashChaining.cpp, hashLinear.cpp, hashQuadratic.cpp
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Namespace declarations                                                    */
/*---------------------------------------------------------------------------*/
using namespace std;
using namespace chrono;

/*---------------------------------------------------------------------------*/
/* Global Declarations                                                       */
/*---------------------------------------------------------------------------*/

// Turn on or off to run the experiment for each data structure
// #define Binary_Search_Tree true


int main(int argc, char *argv[])
{
	ifstream dataFile;
  string dataString;

  const int DATA_SIZE=40000;
  int testData[DATA_SIZE];    //integer array to store the 40,000 elements from the data files
  float time_insert[400]; //array to hold time measurements for insertion
  float time_search[400]; //array to hold time measurements for search


    //error message if invalid arguments
	if (argc != 6)
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


// #if Binary_Search_Tree

    HashTable ht(40009);
    ofstream hashInsertFile, hashSearchFile, hashCollisionFile, searchCollisionFile;

    high_resolution_clock::time_point insert_start, insert_end, search_start, search_end;
    duration<double> execTime;


    hashInsertFile.open(argv[2]);
    hashSearchFile.open(argv[3]);
		hashCollisionFile.open(argv[4]);
		searchCollisionFile.open(argv[5]);

    //error message if output file does not open
	if (!hashInsertFile.is_open())
	{
		cerr << "Could not open " << argv[2] << " for writing!" << endl;
		return 3;
	}
    if (!hashSearchFile.is_open())
	{
		cerr << "Could not open " << argv[3] << " for writing!" << endl;
		return 4;
	}
	if (!hashCollisionFile.is_open())
	{
		cerr << "Could not open " << argv[4] << " for writing!" << endl;
		return 5;
	}
	if (!searchCollisionFile.is_open())
	{
		cerr << "Could not open " << argv[5] << " for writing!" << endl;
		return 5;
	}


    /****
     * INSERTION
     *
    */
    for (int m = 0; m<400; m++)
    {
        // insert_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to insert
				int preNumCollisions = ht.getNumOfCollision();

        for (int i=0; i<100; i++)
        {
            insert_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to insert

            ht.insertItem(testData[100*m+i]);  //inserting 100 elements at a time

            insert_end = high_resolution_clock::now(); //stop the time for the insertion opperation
            execTime = execTime+ duration_cast<microseconds>(insert_end - insert_start);  //the difference bw end and start is how long insertion of 100 elements took

        }

				hashCollisionFile << ht.getNumOfCollision() - preNumCollisions << endl;

        time_insert[m]= execTime.count()/100; //getting average insertion time and storing into array
        hashInsertFile << time_insert[m] << endl;   //writing average insertionn time to file

    }
		// cout << ht.getNumOfCollision() << endl;

    /****
     * SEARCH
     *
    */
    for (int m=0; m<400; m++)
    {

        int randoIndices[100];
        for (int i = 0; i < 100; i++)  //populating array with 100 random values
        {
            randoIndices[i] = rand() % 100*m+100;
        }

				int preNumCollisions = ht.getNumSearchCollision();
        // search_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to search
        for (int i=0; i<100; i++)
        {
            search_start = high_resolution_clock::now(); //starting the timer now to see how long it takes to search

            ht.searchItem(testData[randoIndices[i]]); //searching the BST for 100 data values that are in our BST somewhere

            search_end = high_resolution_clock::now(); //stop the time for the search opperation
            execTime = execTime + duration_cast<microseconds>(search_end - search_start);  //the difference bw end and start is how long search of 100 elements took


        }
				searchCollisionFile << ht.getNumSearchCollision() - preNumCollisions << endl;

        time_search[m]= execTime.count()/100; //storing average search time into an array
        hashSearchFile << time_search[m] << endl;   //writing the search time to the file

    }



// #endif


    dataFile.close();
}
