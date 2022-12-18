/****************************************************************/
/*                    RPNCalculator.cpp                         */
/****************************************************************/
/* Julia Troni       Assignment 5     Zagrodzki CSCI 2270       */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>

using namespace std;

/*
 * Purpose: constructor 
 * @param none
 * @return none
 */
RPNCalculator::RPNCalculator()
{
  stackHead = NULL;
}
/*
 * Purpose: destructor to pop everything off the stack
 * @param none
 * @return none
 */
  RPNCalculator:: ~RPNCalculator()
  {
    Operand * current; 
    while (!isEmpty()) 
    {
      current = stackHead;
      stackHead = stackHead -> next;
      delete current;
    }
  }
 /*
 * Purpose: checks if stack is empty 
 * @param none
 * @return true if the stack is empty, otherwise returns false
 */
  bool RPNCalculator ::isEmpty()
  {
    if (stackHead == NULL)
    {
      return true;
    }
    else {
      return false;
    }

  }
/*
 * Purpose: insert a new node with the number onto the stack
 * @param the number in type float that the user enters
 * @return none
 */
  void RPNCalculator::push(float num)
  {
    Operand * nn = new Operand;
    nn -> number = num;
    if (isEmpty())
    {
      stackHead = nn;
      stackHead -> next = NULL;
    }
    else {
      nn -> next = stackHead; 
      stackHead = nn; 
    }
  }
/*
 * Purpose: deletes the top most item of the stack
 * @param none
 * @return none
 */
  void RPNCalculator:: pop()
  {
    if (isEmpty())
    {
      cout << "Stack empty, cannot pop an item." << endl; 
    }
    else {
      Operand * temp = stackHead;
      stackHead = stackHead -> next;
      delete temp; 
    }
  }
/*
 * Purpose: to return the top most item of the stack
 * @param none
 * @return a pointer to the top of the stack
 */
  Operand* RPNCalculator:: peek()
  {
    if (isEmpty())
    {
      cout << "Stack empty, cannot peek." << endl;
      return NULL;
    }
    else {
      return stackHead; 
    }
  }
/*
 * Purpose: perform the arithmetic operation, either + or *, on the top 2 numbers in the stack
 * @param the symbol "+" or "*" which indicates which operation to perform on the numbers 
 * @return true if the operation was carried out successfully 
 */
  bool RPNCalculator::compute(std::string symbol)
  {
    float add, mult, first, second; 

    if (symbol == "+")
    {
        if (isEmpty())
      {
        cout << "err: not enough operands" << endl;
        return false;
      }
      first = getStackHead()->number;
      pop();
      if (isEmpty())
      {
        cout << "err: not enough operands" << endl;
        push(first);
        return false;
      }
      else
      {
        second = getStackHead()->number;
        pop();
      }
      add = first + second;
      push(add);
      return true;
    }
    else if (symbol == "*")
    {
        if (isEmpty())
      {
        cout << "err: not enough operands" << endl;
        return false;
      }
      first = getStackHead()->number;
      pop();
      if (isEmpty())
      {
        cout << "err: not enough operands" << endl;
        push(first);
        return false;
      }
      else
      {
        second = getStackHead()->number;
        pop();
      }
      mult = first*second ;
      push(mult);
      return true;
    }
    else {
      cout << "err: invalid operation" <<endl;
      return false;
    }
  }
