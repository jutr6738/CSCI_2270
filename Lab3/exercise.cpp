#include <iostream>
#include <fstream>

using namespace std;


int* resize(int* arrayPtr, int &capacity)
{
	//increase the capacity by two times
	int newCapacity = 2*capacity;
    cout<<"Resizing from "<<capacity<<" to "<<newCapacity<<endl;

	//dynamically allocate an array of size newCapacity
	 int *newArray = new int[newCapacity];

	// copy all data from oldArray to newArray
	for (int i=0; i< capacity; i++)
	{
		newArray[i]=arrayPtr[i];
	}
	//free the memory associated with oldArray
	delete [] arrayPtr;

	capacity = newCapacity;

	// return the newArray
	return (newArray);
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		return -1;
	}
	string filename = argv[1];
	ifstream data;
	data.open(filename.c_str());

	int capacity = 10;
	int *arrayPtr;

	//Dynamically allocate space here for the array
	arrayPtr = new int[capacity];
	int numOfElement = 0;
	string temp;

	if(data.is_open())
	{
		while(getline(data, temp))
		{
			int toBeInsert = stoi(temp);
			if(numOfElement == capacity)
			{
				
				arrayPtr = resize(arrayPtr, capacity);
			}
			arrayPtr[numOfElement] = toBeInsert;
			numOfElement++;
		}
		data.close();
	}

	for(int i = 0; i < numOfElement; i++)
	{
		cout << "Num: " << arrayPtr[i] << endl;
	}
	return 0;
}
