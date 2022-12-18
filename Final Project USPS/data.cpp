
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;



int main(int argc, char *argv[])
{
	ifstream dataFile;
    string dataString;
    ofstream dataList; 

    const int DATA_SIZE=40000;
    int testData[DATA_SIZE];    //integer array to store the 40,000 elements from the data files




	dataFile.open(argv[1]);     //opening data file for reading
    dataList.open(argv[2]); 

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
    for (int i=0; i<DATA_SIZE; i=i+100)
    {
      dataList << testData[i]<< endl;
    }


}