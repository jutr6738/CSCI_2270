#include "LinkedList.h"

using namespace std;

// Add a new node to the list
void LinkedList::insert(Node* prev, int newKey){

  //Check if head is Null i.e list is empty
  if(head == NULL){
    head = new Node; //creating a new memory in heap and head is ptr to that location 
    head->key = newKey; //(*head).key= new key 
    head->next = NULL;  //null basically says end of linked list 
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL) //want to insert at beginning 
  {
      Node* newNode = new Node; //creating new node we want it to point to head 
      newNode->key = newKey;
      newNode->next = head; //new node is pointing to head 
      head = newNode; //now we need to make head point to this new node 
  }

  else{

      Node* newNode = new Node;
      newNode->key = newKey;
      newNode->next = prev->next; //we want the new nodes to point to what the previous one was pointing to. aka the new node's arrow needs to be what the previous node's was
      prev->next = newNode; //now changing the previous next to point to the new node now

    }
  }


// TODO: SILVER PROBLEM
// Delete node at a particular index
bool LinkedList::deleteAtIndex(int n)
{
  bool isDeleted = false;

  if(head == NULL){
    cout<< "List is already empty"<<endl;
    return isDeleted;
  }

  // Special case to delete the head
    if (n == 0) { //we want to delete index 0
        Node *temp = new Node; 
        temp = head; 
        head = temp -> next; 

        delete temp;

        return true;
    }

int counter=0; //counter is zero bc we are at the head 
  Node *pres = head;  //set the current (pres) node to head 
	Node *prev = NULL;  //bc there is no previous of the head we have it point to a null value 

  
    while (counter!=n)
    {
      prev= pres; //must hold the prev bc if you move to the next node we won't be able to get the prev
      pres= pres-> next;  //move to the next one 
      counter++;  //then we keep incrementing until we get to n
    }

    prev-> next = pres -> next; //bc now we need the previous to point to n's next (n is the index where pres is)
    delete pres; 
    isDeleted= true;
  

	return isDeleted;
}

// TODO: GOLD PROBLEM
// Swap the first and last nodes (don't just swap the values)
bool LinkedList::swapFirstAndLast()
{
    bool isSwapped = false;

    if(head == NULL) {
        cout << "List is empty. Cannot swap" << endl;
        return false;
    }

    // TODO (take care of the edge case when your linkedlist has just 2 nodes)


    return isSwapped;
}

// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}

// Search for a specified key and return a pointer to that node
Node* LinkedList::searchList(int key) {

    Node* ptr = head;
    while (ptr != NULL && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}
