#include <iostream>
#include <fstream>
#include <string>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
//constructor. sets root to null
MovieTree::MovieTree()
{
	root = NULL;
}


//helper for deleteTree() to delete linked list
void deleteLinkedList(LLMovieNode* curr){
	LLMovieNode* next;
	while(curr != NULL){
		next = curr->next;
		delete curr;
		curr = next;
	}
}
//helper for destructor to delete all BST nodes
void deleteTree(TreeNode *T){
	if (T == NULL) 
    {
        return;
    }

	deleteTree(T->leftChild);
    deleteTree(T->rightChild);
    deleteLinkedList(T->head);
    delete T;
}
//destructor- deletes all. Calls helper function deleteTree
MovieTree :: ~MovieTree(){
	deleteTree(root);
	root = NULL;
}




//helper function for TprintinOrder() to print the movies stored in the LL
void LLprintinOrder(LLMovieNode *m)
{
    if (m!=NULL)
    {
        cout<< " >> " << m-> title << " " << m->rating << endl; 
        LLprintinOrder(m-> next); 
    }
}

//helper function for printMovieInventory()
//calls the helper function LLprintinOrder()
void TprintinOrder(TreeNode * t)
{
  if (t != NULL)
  {
    TprintinOrder(t ->leftChild);
    cout << "Movies starting with letter: " << t -> titleChar << endl;
    LLprintinOrder(t->head);
    TprintinOrder(t ->rightChild);
  }
}

//prints every moovie in the data structure in alphabetical order of titles
//calls the helper function TprintinOrder()
void MovieTree::printMovieInventory()
{
    TprintinOrder(root);
}

//helper function for addMovie()
TreeNode * addHelper(TreeNode *m, TreeNode* p, int ranking, string title, int year, float rating)
{
    char letter= title[0]; 
   
    //case 1: if no tree node with the letter
    if (m==NULL)
    {
        //creating the new tree node
        m= new TreeNode;
        m-> titleChar = letter;
        m->parent = p;
        //creating the linked list 
        m->head= new LLMovieNode(ranking, title, year, rating);
    }
    //sorting the new tree node based on alphabetical order
    else if (m-> titleChar < letter)
    {
        m -> rightChild = addHelper(m -> rightChild, m, ranking, title, year, rating);
    }
    else if (m-> titleChar > letter)
    {
        m -> leftChild = addHelper(m -> leftChild, m, ranking, title, year, rating); 
    }
    
    //there is already a tree node with TreeLetter so just need to add the movie to the linked list
    else 
    {    
        //creating the linked list node 
        LLMovieNode *newone=new LLMovieNode(ranking, title, year, rating);
       
        //traversal to insert in alphabetical order
        LLMovieNode * crawler =m->head;  
        if (crawler -> title > title)
        {
            newone-> next = crawler;
            m->head= newone;
            return m;
        }
        while (crawler->next !=NULL && crawler->next->title < title)
        {
            crawler=crawler-> next; 
        }
        newone-> next= crawler-> next;
        crawler-> next= newone;
    }
    
    return m; 
}

//adds a movie to the data structure in the correct place based on its title 
//calls addHelper() helper function
void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    root=addHelper(root, NULL, ranking, title, year, rating); 
}




TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}




TreeNode *getMin(TreeNode *curr)
{
    //keeps going left to get the minimum 
    if (curr->leftChild==NULL)
    {
        return curr;
    }
    return getMin(curr->leftChild);
}

TreeNode *deleteBST(TreeNode *m, char letter)
{
    if (m==NULL)
    {
        return NULL;
    }
    else if (m-> titleChar > letter)
    {
        m-> leftChild= deleteBST(m->leftChild, letter);
        if (m->leftChild != NULL)
        {
            m-> leftChild->parent= m;
        }
    }
    else if (m->titleChar < letter)
    {
        m->rightChild= deleteBST(m->rightChild, letter);
        if (m -> rightChild != NULL)
        {
            m-> rightChild->parent= m;
        }
    }
    else //we found the node with the correct letter
    {
        if (m->leftChild == NULL && m->rightChild ==NULL) //no child
        {
            delete m;
            return NULL;
        }
        else if (m->leftChild==NULL) //only right child
        {
            TreeNode *temp=m;
            m=m->rightChild;
            delete temp;

            return m;
        }
        else if (m->rightChild == NULL) //only left child 
        {
            TreeNode *temp=m;
            m=m->leftChild;
            delete temp;

            return m;
        }
        else //both left and right child
        {
            //replace with min of right subtree -> calls getMin()
            TreeNode * min= getMin(m->rightChild);
            m->titleChar= min-> titleChar;
            m->head= min->head;
            m->rightChild =deleteBST(m->rightChild, min->titleChar);

            return m;
        }
        
    }

    return m; 
}


void deleteLL(TreeNode * BSTNode, TreeNode *& root, string title)
{

    char letter= title[0];
    LLMovieNode* curr= BSTNode->head;
        
    
        if (curr-> next == NULL && curr-> title== title) //only one movie in LL
        {
            delete curr; 
            root = deleteBST(root, letter); //now the LL is empty so deleting the BST node 
        }

        else if (curr -> next != NULL && curr -> title == title)
        {
            LLMovieNode *temp;
            temp= curr;
            curr= temp->next; 
            BSTNode ->head = curr;
            delete temp; 
        }

        else //multiple movies in the list
        {
            
            while (curr -> next != NULL && curr-> next -> title != title) //traverse until we find the movie
            {
                curr= curr->next;
            }
            LLMovieNode *temp;
            temp= curr-> next;
            if (temp != NULL)
            {
                curr->next= temp->next; 
                delete temp; 
            }
        }
    
}

//deletes the linked list node that contains the title 
void MovieTree::deleteMovie(std::string title)
{
    char letter= title[0];
    TreeNode * BSTNode= searchChar(letter); //finding the BST node that starts with the letter of the movie
    
    if (BSTNode == NULL) //movie not found
    {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return; 
    }

    deleteLL(BSTNode, root, title);

}


void MovieTree::leftRotation(TreeNode* x)
{
    
     TreeNode * y= x->rightChild;
        x->rightChild = y-> leftChild; 

        if (y->leftChild != NULL)
        {
            y->leftChild -> parent = x; 
        }
        y->parent = x-> parent;

        if (x-> parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent -> leftChild)
        {
            x->parent->leftChild =y;
        }
        else 
        {
            x->parent->rightChild= y;
        }

        y->leftChild =x;
        x->parent =y; 
}




//------ Given Methods--------//
void _grader_inorderTraversal(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}
