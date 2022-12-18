#include <iostream>
#include "BST.hpp"
using namespace std;


/**
 Create a node with key as data 
 **/

Node* BST:: createNode(int data)
{
    Node* newNode = new Node;
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BST::BST()
{

}

/**
parameterized constructor to create the root and put the data in the root.
**/
BST::BST(int data)
{
    root = createNode(data);
    cout<< "New tree created with "<<data<<endl;
}

/**
Destructor
**/

BST::~BST(){
     destroyNode(root);
}


Node* BST::getRoot(){
    return root;
}

 /**
 This function will destroy the subtree rooted at currNode.
 **/
void BST:: destroyNode(Node *currNode){
     if(currNode!=NULL)
     {
         destroyNode(currNode->left);
         destroyNode(currNode->right);

         delete currNode;
         currNode = NULL;
     }
 }



//---------------------------- INSERT NODE IN THE TREE --------------------------------------

/**
This function will add the data in the tree rooted at currNode.
We will call this function from addNode.
**/
Node* BST:: addNodeHelper(Node* currNode, int data)
{
    if(currNode == NULL){
        return createNode(data);
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left,data);
    }
    return currNode;

}


void BST:: addNode(int data)
{
    root = addNodeHelper(root, data);
}

//-----------------------------------------PRINT TREE WITH INORDER TRAVERSAL--------------------------------

/** This function will traverse the tree in-order and print out the node elements.
printTree() function will call this function.
**/
void BST:: printTreeHelper(Node* currNode){
     if(currNode)
     {
        printTreeHelper( currNode->left);
        cout << " "<< currNode->key;
        printTreeHelper( currNode->right);
     }
 }

void BST:: printTree(){
     printTreeHelper(root);
     cout<<endl;
}

 //------------------------------------------------SEARCH A KEY------------------------------------------
 /** This function will search the data in a tree
     We will call this function from searchKey.
 **/
Node* BST::searchKeyHelper(Node* currNode, int data){
    if(currNode == NULL)
        return NULL;

    if(currNode->key == data)
        return currNode;

    if(currNode->key > data)
        return searchKeyHelper(currNode->left, data);

    return searchKeyHelper (currNode->right, data);
}

// This function will return true if a key is in the tree and false if it is not 
bool BST::searchKey(int key){
    Node* tree = searchKeyHelper(root, key);
    if(tree != NULL) {
        return true;
    }
    cout<<"Key not present in the tree"<<endl;
    return false;
}

//--------------------------- Get Min value Node ------------------------------------------------

//This function will return a pointer to the node with the minimum value. Called in deleteNode function 
Node* BST::getMinValueNode(Node* currNode){

    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}


//--------------------------- Delete a Node ------------------------------------------------

// This function deletes the Node with 'value' as it's key.
Node* BST::deleteNode(Node *currNode, int value)
{

  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->key)
  {
    currNode->left = deleteNode(currNode->left, value);
  }
  else if(value > currNode->key)
  {
    currNode->right = deleteNode(currNode->right, value);
  }
  // We found the node with the value
  else
  {
    //Case 1: No child
    if(currNode->left == NULL && currNode->right == NULL)
    {//call delete on currNode and return NULL
        delete currNode;
        return NULL;

    }
    //Case 2: Only right child
    else if(currNode->left == NULL)
    {//store currNode in temp ; then currNode = currNode-> right ; then delete temp ; return currNode which is basically the right node of the one we just deleted
        Node *temp=currNode;
        currNode=currNode->right;
        delete temp;

        return currNode;
    }
    //Case 3: Only left child
    else if(currNode->right == NULL)
    {
        Node *temp = currNode;
        currNode=currNode->left;
        delete temp;
        
        return currNode;

    }
    //Case 4: Both left and right child
    else
    {
        //Deletes and replaces with Minimum from right subtree by calling getMinValueNode
        Node *min = getMinValueNode(currNode->right);
        currNode->key=min->key;
        currNode = deleteNode(currNode->right,min->key);
        
        return currNode;
    }

  }
return currNode;
}


