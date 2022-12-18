/****************************************************************/
/*                    ProducerConsumer.cpp                   */
/****************************************************************/
/* Julia Troni       Assignment 5     Zagrodzki CSCI 2270       */
/****************************************************************/


#include "ProducerConsumer.hpp"
#include <iostream>

using namespace std;


/*
 * Purpose: constructor 
 * @param none
 * @return none
 */
ProducerConsumer::ProducerConsumer()
{
    queueFront = 0;
    queueEnd = 0;
}
/*
 * Purpose: checks if the queue is empty
 * @param none
 * @return true if queue is empty, otherwise false 
 */
bool ProducerConsumer::isEmpty()
{
    if (counter==0)
    {
        return true;
    }
    else {
        return false;
    }
}
/*
 * Purpose: checks if the queue is full
 * @param none
 * @return true if queue is full, otherwise false
 */
bool ProducerConsumer::isFull()
{
    if (counter == SIZE)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
/*
 * Purpose: adds the item to the end of the queue 
 * @param string to store in the array
 * @return none
 */
void ProducerConsumer::enqueue(std::string item)
{
    if (!isFull())
    {
        queue[queueEnd]= item; 
        counter++;
        if (queueEnd== SIZE-1)
        {
            queueEnd=0;
        }
        else{
            queueEnd++;
        }
    }
    else{
        cout << "Queue full, cannot add new item"<< endl;
    }
}
/*
 * Purpose: removes the first item of the queue
 * @param none
 * @return none
 */
void ProducerConsumer::dequeue()
{
    string de;
    if (!isEmpty())
    {
        de=queue[queueFront];
        counter--;
        if (queueFront ==SIZE-1)
        {
            queueFront=0;
        }
        else 
        {
            queueFront++;
        }
    }
    else{
        cout << "Queue empty, cannot dequeue an item" << endl;
    }
}
/*
 * Purpose: returns the first item in the queue
 * @param none
 * @return if empty returns empty string, else returns the first item in the queue
 */
std::string ProducerConsumer::peek()
{
    if (isEmpty())
    {
        cout<< "Queue empty, cannot peek" <<endl;
        return "";
    }
    else {
        return queue[queueFront]; 
    }
}
/*
 * Purpose: returns the number of items in the queue
 * @param none
 * @return the number of items in the queue
 */
int ProducerConsumer::queueSize()
{
    return counter; 
}  
