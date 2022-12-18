/**CPPFile*********************************************************************
   FileName    [minHeap.cpp] 
   
   PackageName [none]

   Synopsis    [Implementation of minHeaps and heap sort.]

   Description []   

   SeeAlso     []       

   Author      [

   Asa Ashraf (asa.ashraf@colorado.edu)
   Ashutosh Trivedi (ashutosh.trivedi@colorado.edu)
   Maciej Zagrodzki (maciej.zagrodzki@colorado.edu)

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

#include <iostream>
#include <fstream>
#include <chrono>


/*---------------------------------------------------------------------------*/
/* Namespace declarations                                                    */
/*---------------------------------------------------------------------------*/
using namespace std;
using namespace chrono;

/*---------------------------------------------------------------------------*/
/* Global Declarations                                                       */
/*---------------------------------------------------------------------------*/
#define COUNT 10
const int ARRAY_SIZE = 30; //20e3;


class MinHeap
{
private:
  int *heap;
  int capacity;
  int currentSize;

public:
  MinHeap()
  {
    capacity = 10; // default capacity
    currentSize = 0;
    heap = new int[capacity];
  }

  MinHeap(int s)
  {
    capacity = s;
    currentSize = 0;
    heap = new int[capacity];
  }

  ~MinHeap()
  {
    delete[] heap;
  }

  void push(int value)
  {
    if (currentSize == capacity)
    {
      cout << "Heap overflow" << endl;
    }
    else
    {
      currentSize++;
      heap[currentSize - 1] = value;  //inserting value at highest unoccupied index 

      int i = currentSize - 1;
      while (parent(i) >= 0 && heap[i] < heap[parent(i)]) //as long as the minheap property is not satisfied
      {
        swap(heap[i], heap[parent(i)]); //we will swap the elements 
        i = parent(i);
      }
    }
  }

  int pop()
  {
    if (currentSize <= 0)
    {
      cout << " Heap is empty: returning garbage" << endl;
      return -1;
    }
    else
    {
      int result = heap[0];
      heap[0] = heap[currentSize - 1];  //replacing the 0 index with the value at the last index
      currentSize = currentSize - 1;  //decrement the size 
      minHeapify(0);  //now calling heapify to resort it so that the heap follows minheap properties
      return result;
    }
  }

  int peek()
  {
    if (currentSize <= 0)
    {
      cout << " Heap is empty: returning garbage" << endl;
      return -1;
    }
    else
      return heap[0];
  }

  void printHeap()
  {
    cout << "=====================================================" << endl;
    print2DUtil(0, 0);
    cout << "=====================================================" << endl;
  }

  void traverseAndPrint(int i)
  {
    traversePrint(i);
  }

private:
  void minHeapify(int index)  //does the sorting so that the minheap property is satisfied 
  {
    int min = index;
    if (leftChild(index) < currentSize) //if a left child exists 
    {
      if (heap[min] > heap[leftChild(index)]) //compare the values to find the smallest of them 
        min = leftChild(index);
    }
    if (rightChild(index) < currentSize)  //if it has a right child
    {
      if (heap[min] > heap[rightChild(index)])  //compare the values to find the smallest of them
        min = rightChild(index);  
    }

    if (index == min)
    {
      // Already heapified
      return;
    }
    else
    {
      swap(heap[min], heap[index]);
      minHeapify(min);
    }
  }
  int parent(int index) { return (index - 1) / 2; }
  int leftChild(int index) { return 2 * index + 1; }
  int rightChild(int index) { return 2 * index + 2; }
  void swap(int &x, int &y)
  {
    int z = x;
    x = y;
    y = z;
  }

  void print2DUtil(int root, int space)
  {
    if (root >= currentSize)
      return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    if (rightChild(root) < currentSize)
      print2DUtil(rightChild(root), space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
      cout << " ";
    cout << heap[root] << "\n";

    // Process left child
    if (leftChild(root) < currentSize)
      print2DUtil(leftChild(root), space);
    // cout << "Heap: ";
    // for (int i = 0; i < currentSize; i++) {
    //   cout<< heap[i] << " ";
    // }
    // cout << endl;
  }
  void traversePrint(int i)
  {
    ofstream myfile;
    myfile.open("tree.dot");
    myfile << "digraph graphname {" << endl;
    myfile << "node [margin=0 fontcolor=black style=filled]" << endl;
    if (currentSize > 0)
    {
      myfile << heap[i] << " [fillcolor = yellow];" << endl;
      printTree(myfile, 0);
    }
    myfile << "}" << endl;
    myfile.close();
    system("dot -Tpdf tree.dot> tree.pdf; open tree.pdf");
    getchar();
  }

  void printTree(ofstream &myfile, int root)
  {
    if (root >= currentSize)
      return;
    else
    {
      if (leftChild(root) < currentSize)
      {
        myfile << heap[root] << "->" << heap[leftChild(root)] << "[label=left];" << endl;
        printTree(myfile, leftChild(root));
      }
      if (rightChild(root) < currentSize)
      {
        myfile << heap[root] << "->" << heap[rightChild(root)] << "[label=right];" << endl;
        printTree(myfile, rightChild(root));
      }
    }
    return;
  }
};

void printArray(int a[], int size)
{
  for (int i = 0; i < size; i++)
    cout << a[i] << " ";
}

/**Function********************************************************************
   
   Synopsis    [The "main" function]
   
   Description [optional]
   
   SideEffects [required]
   
   SeeAlso     [optional]
   
******************************************************************************/
int main()
{
  high_resolution_clock::time_point start, end;
  duration<double> execTime;

  MinHeap MH(ARRAY_SIZE);
  int testArr[ARRAY_SIZE], arr[ARRAY_SIZE], arr2[ARRAY_SIZE];

  for (int i = 0; i < ARRAY_SIZE; i++)  //populating array with random values 
  {
    testArr[i] = rand() % 1000;
    arr2[i] = testArr[i];
  }

  cout << "the unsorted test array is: " << endl;
  printArray(testArr, ARRAY_SIZE);  //printing that array
  cout << "\n\n";

  start = high_resolution_clock::now(); //starting the timer now to see how long it takes to sort 

  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    MH.push(testArr[i]);    //pushing all values from the initial array into min heap 
  }

  // MH.printHeap();
  // getchar();

  for (int i = 0; i < ARRAY_SIZE; i++)
  { arr[i] = MH.pop();  //poping all the valoues from the now sorted array and poping them into a different array to save them
  }

  end = high_resolution_clock::now(); //stop the tiime 
  execTime = duration_cast<microseconds>(end - start);  //the difference bw end and start is how long heapsort took 

  cout << "\n Heapsort execution time: " << execTime.count() << " seconds." << endl;

  cout << "\n the Heap sorted array is: " << endl;
  //printArray(arr,ARRAY_SIZE);


//now we will time how long bubble sort takes 
  start = high_resolution_clock::now();

  for (int i = ARRAY_SIZE - 1; i > 0; i--)  //performing bubble sort 
  {
    for (int j = 0; j < i; j++)
      if (arr2[j] > arr2[j + 1])
      {
        int temp = arr2[j + 1];
        arr2[j + 1] = arr2[j];
        arr2[j] = temp;
      }
  }

  end = high_resolution_clock::now();

  execTime = duration_cast<microseconds>(end - start);
  cout << "\nbubble execution time: " << execTime.count() << " seconds." << endl;

  cout << "\nthe bubble sorted array is: " << endl;
  //printArray(arr,ARRAY_SIZE);

  return 0;
}
