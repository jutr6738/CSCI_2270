/*---------------------------------------------------------------------------*/
// Author of linkedList.hpp.cpp, linkedList.cpp, linkedListDriver.cpp:
// Julia Troni
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
//Linked List header file utilized in linkedList.cpp, linkedListDriver.cpp
/*---------------------------------------------------------------------------*/



#include <iostream>

struct Node{
      int key;
      Node *next;
};

class LinkedList
{
  private:
    Node *head;

  public:
    LinkedList(){
    	head = NULL;
    }
    void insert(Node *prev, int newKey);
    Node* searchList(int key);
    bool deleteAtIndex(int index);
    void printList();
};