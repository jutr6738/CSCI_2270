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
//if index is full, checks index + i until empty index is found
bool HashTable::insertItem(int key)
{
  unsigned int index = hashFunction(key);
  if(table[index] == NULL){
    table[index] = createNode(key, nullptr);
    return true;
  }
  else{
    numOfcolision++;
    int i = 1;
    while(table[(index + i) % tableSize] != NULL){
      i++;
    }
    table[(index + i)% tableSize] = createNode(key, nullptr);
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
    if(table[i]){
      cout << table[i]->key << "  ";
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
//incriments i for (index + i) until the node's key at (index + i) equals
//argument, returns node at this index.
node* HashTable::searchItem(int key)
{
  unsigned int index = hashFunction(key);
  int i = 0;
  while(table[(index + i)% tableSize]->key != key){
    numSearchCollision++;
    i++;
  }
  return table[(index + i) % tableSize];
}
