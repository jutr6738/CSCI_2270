/*---------------------------------------------------------------------------*/
// Author of hashChaining.cpp, hashLinear.cpp, hashQuadratic.cpp:
// Annikka Turmala
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
//Hash header file utilized in hashChaining.cpp, hashLinear.cpp,
//and hashQuadratic.cpp
/*---------------------------------------------------------------------------*/

#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;
    int numOfcolision = 0;
    int numSearchCollision = 0;
    node* createNode(int key, node* next);

public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    bool insertItem(int key);

    // hash function to map values to key
    unsigned int hashFunction(int key);

    void printTable();
    int getNumOfCollision();
    int getNumSearchCollision();
    node* searchItem(int key);
};

#endif
