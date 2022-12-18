#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{

  int foo[] = {1, 2, 3, 4, 5};

  cout << "Addresses of elements:" << endl;
  //Print the addresses of array elements
  
  for (int i=0; i<5; i++)
  {
    cout << foo+i << " ";
    // same as cout << &(ptr+i) << endl;
  }

  cout << endl;

  cout << "Elements:" << endl;;
  //Print all values of the elements using pointers
  
  int *ptr = foo;
    for (int i=0; i<5; i++)
  {
     cout << *(ptr+i) << " "; //prints 1,2,3,4,5
  }


  return 0;
}
  
  