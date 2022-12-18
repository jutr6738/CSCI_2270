#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


//constructor: initializes root to null
MovieTree::MovieTree() {
 root = NULL;  
}

//helper function to delete all nodes using post order traversal
void destroyPostOrder(MovieNode *destroy)
{
  if (destroy != NULL)
  {
    destroyPostOrder(destroy -> left);
    destroyPostOrder(destroy->right);
    delete destroy;
  }
}

//destructor: frees all memory that was allocated
//calls destroyPostOrder() helper function
MovieTree::~MovieTree() {
  destroyPostOrder(root);
  root=NULL;
}

//helper function for printMovieInventory()
void printinOrder(MovieNode * curr)
{
  if (curr != NULL)
  {
    printinOrder(curr ->left);
    cout << "Movie: " << curr -> title << " " << curr -> rating << endl;
    printinOrder(curr ->right);
  }

}

//prints every node in the tree in alphabetical order of the titles
//calls printinOrder() helper function
void MovieTree::printMovieInventory() {
  if (root == NULL)
  {
    cout << "Tree is Empty. Cannot print" << endl;
  }
  printinOrder(root);

}

//helper function for addMovieNode() to add nodes to the tree in the correct place based on alphabetical order of titles 
MovieNode * addHelper (MovieNode * n, int ranking, string title, int year, float rating)
{
  //Case 1: BST is empty or need to add a node 
   if (n == NULL)
   {
     n = new MovieNode(ranking, title, year, rating);
     return n;
   }

   else if (n-> title < title)
   {
     n -> right = addHelper(n -> right, ranking, title, year, rating);
   }
  else if (n-> title > title)
   {
     n -> left = addHelper(n -> left, ranking, title, year, rating);
   }

   return n; 
  
}

//Adds a node to the tree in the correct place based on alphabetical order of the titles
//calls addHelper
void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  root= addHelper(root, ranking, title, year, rating);

}

void findHelper(MovieNode *curr, string title)
{
  if (curr != NULL)
  {
    if (curr -> title == title) //found
    {
      cout << "Movie Info:" << endl;
      cout << "==================" << endl;
      cout << "Ranking:" << curr->ranking << endl;
      cout << "Title  :" << curr->title << endl;
      cout << "Year   :" << curr-> year << endl;
      cout << "rating :" << curr-> rating << endl;
    }
    else if (curr -> title > title) //too far down the alphabet, we need closer to A, move left
    {
      findHelper(curr -> left, title);
    }
    else if (curr -> title < title) //too low in the alphabet, we need closer to Z, move right
    {
      findHelper(curr -> right, title);
    }
  }
  else //could not find
  {
    cout << "Movie not found." << endl;
  }
}

//finds the movie with the given title and prints out it's information 
//uses the helper function findHelper()
void MovieTree::findMovie(string title) {
  findHelper(root, title);

}

//if finds movies that meet the constraints, returns true and prints those movies 
void queryHelp(MovieNode *m, float rating, int year)
{

  if ( m!= NULL)
  {
    if (m -> year > year && m -> rating >= rating)
    {
      cout<< m->title << "(" << m->year << ") " << m-> rating << endl; 
    }
    queryHelp(m->left, rating, year);
    queryHelp(m->right, rating, year);
  }
}


//prints all the movies whose rating is at least as good as the input parameter rating and that are newer than the year
void MovieTree::queryMovies(float rating, int year) {
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  queryHelp(root, rating, year);
 
}

//helper function for averageRating() to calculate the number of movies in the binary tree 
int countHelper(MovieNode *m) {
  if(m==NULL)
  {
    return 0.0;
  }
    int count=0;
    count+=countHelper(m->left);
    count+=countHelper(m->right);
    count+=1;
    
    return count; 
}
//helper function for averageRating() to calculate the sum of the ratings of all of the movies in the tree
float rateHelper(MovieNode *m) {
  if(m==NULL)
  {
    return 0.0;
  }
    float rate=0.0;
  
    rate+=rateHelper(m->left);
    rate+=rateHelper(m->right);
    rate+=m->rating;
    
    return rate; 
}

//prints the average rating for all movies in the tree. If the tree is empty prints 0.0. Calles countHelper and rateHelper
void MovieTree::averageRating() {
  cout << "Average rating:";
  if (countHelper(root)==0)
  {
    cout << "0.0" << endl;
  }
  else 
  {
    cout << rateHelper(root)/countHelper(root) << endl;
  }
}

//helper function for printLevelNodes 
void levelHelper(MovieNode * m, int level)
{
  if (m==NULL)
  {
    return;
  }
  else if (level == 0)
  {
    cout << "Movie: " << m-> title << " " << m->rating << endl; 
  }
  else
  {
    levelHelper(m->left, level-1);
    levelHelper(m->right, level-1);
  }
}

//prints all the nodes in the tree from left to right that are at the depth=level from the root of the tree, calles levelHelper() 
void MovieTree::printLevelNodes(int level) {
  levelHelper(root, level);
}