#include <iostream>
#include "hash.hh"
using namespace std;

//creates a node to be in hash 'buckets'
//used in insertItem()
//dynamically allocates space for a node and assigns
//arguments key and next to new node. Returns new node.
node* HashTable::createNode(int key, node* next)
{
  node* nn = new node;
  nn->key = key;
  nn->next = next;
  return nn;
}

//constructor. Dynamically creates array size argument 'bsize' for
//Hash Table pointer member 'table' to point to. Sets all hash buckets to NULL
HashTable::HashTable(int bsize)
{
  tableSize = bsize;
  table = new node*[tableSize];
  for(int i = 0; i < tableSize; i++){
    table[i] = NULL;
  }
}

//inserts a key into hash table
//inserts at hash value index
//if index is full, adds key value to linked list at index
bool HashTable::insertItem(int key)
{
  unsigned int index = hashFunction(key);
  if(table[index] == NULL){
    table[index] = createNode(key, nullptr);
    return true;
  }
  else{
    numOfcolision++;
    node* curr = table[index];
    while(curr->next != nullptr){
      curr = curr->next;
    }
    curr->next = createNode(key, nullptr);
    return true;
  }
  return false;
}

// hash function to map values to key
unsigned int HashTable::hashFunction(int key)
{
  return key % tableSize;
}

//prints all keys in table index order
void HashTable::printTable()
{
  for(int i = 0; i < tableSize; i++){
    cout << table[i]->key << "  ";
    node* curr = table[i];
    while(curr->next != nullptr){
      cout << curr->next << "  ";
    }
  }
}

//returns Hash Table data member 'numOfcolision'
int HashTable::getNumOfCollision()
{
  return numOfcolision;
}

//returns Hash Table data member 'numSearchCollision'
int HashTable::getNumSearchCollision()
{
  return numSearchCollision;
}

//searches for node stored in hash table based on key
//gets hash value of key
//goes through LL at hash index until node is found, returns pointer to node
//if node is not found, returns nullptr
node* HashTable::searchItem(int key)
{
  unsigned int index = hashFunction(key);
  node* curr = table[index];
  while(curr->next != nullptr){
    if(curr->key == key){
      return curr;
    }
    else{
      numSearchCollision++;
      curr = curr->next;
    }
  }
  return nullptr;
}
