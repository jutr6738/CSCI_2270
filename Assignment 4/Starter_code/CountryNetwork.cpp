/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
/* finished. do not touch. */
    head = NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    
    // if we are passed an empty list, just create a new head node, and return
    if (head == NULL)
    {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        head = new Country;
        head->name = countryName;
        head->numberMessages = 0;
        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        //case where it's a new head Country
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country *c = new Country;
        c->name = countryName;
        c->numberMessages = 0;
        c->next = head;
        head = c;
    }else{
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
        Country *newCountry = new Country;
        newCountry->name = countryName;
        newCountry->numberMessages = 0;
        newCountry->next = previous->next;
        previous->next = newCountry;
    }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    
    Country * deletethis= searchNetwork(countryName);

    if (deletethis == NULL) //country not found
    {   cout << "Country does not exist." << endl;
    }

    else if (deletethis == head)    //want to delete the first node
    {
        head = head -> next;    //head will now start at the second node bc we are deleting the first one 
        delete deletethis;
    }

    else {

        Country * prev = head; //starting at the head 
        while (prev -> next -> name != countryName) //traversing until we find the node right before the one we are deleting 
        {
            prev= prev -> next; 
        }
        prev ->next = deletethis -> next; //reconnecting from prev to after the deleted node 
        delete deletethis;  //freeing memory of the chosen node 
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    int num_countries = 6;
    string countries[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
    // deleteEntireNetwork();
    Country* prev = NULL;
    for(int i = 0; i < num_countries; i++)
    {
        insertCountry(prev, countries[i]);
        prev = searchNetwork(countries[i]);
    }
}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
// Search until the head is NULL, or we find the country
    Country* ptr = head;
    while (ptr != NULL && ptr->name != countryName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
* Purpose: Creates a loop from last node to the country specified.
* @param countryName name of the country to loop back
* returns pointer to last node before loop creation (to break the loop)
*/
Country* CountryNetwork::createLoop(string countryName)
{
    Country * looper = searchNetwork(countryName); 


    if (looper== NULL)    //if list is empty
    {
        return;
    }

    Country * tail = head;
    while (tail -> next != NULL)
    {
        tail = tail -> next; 
    }
    tail -> next = looper ;
    
    return (tail);
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
  if (head != NULL) //checking that list is not empty
  {

      if (head -> next == NULL)  //only one element in list 
      {
        delete head; 
      }
      
      Country * temp = head; 

      while (temp -> next != NULL)  //until end of list 
      {
          head = temp -> next; 
          cout << "deleting: " << temp -> name << endl;
          delete temp;
          temp = head;
      }
      cout << "deleting: " << temp -> name << endl;
      delete temp; 
      head = NULL; 
      cout << "Deleted network" << endl;
  }
}

/*
*Purpose: to detect loop in the linkedlist
* @param
* returns true if loop is detected. Otherwise return false.
*/
bool CountryNetwork::detectLoop() {
    if (head == NULL)
    {
        return false;
    }
    Country * fast =head -> next;
    Country * slow = head;
    while (fast != NULL && fast-> next != NULL && slow != NULL)
    {
        if (fast == slow)
        {
            return true;
        }
        else 
        {
            fast = fast -> next -> next;
            slow = slow -> next; 
        }
    }
    return false;
}

/*
* Purpose: Take the chunk of nodes from start index to end index
*          Move that chunk at the end of the List
*@param: start index
*@param: end index
* return none
*/
void CountryNetwork:: readjustNetwork(int start_index, int end_index)
{
    if (head == NULL)
    {
        cout << "Linked List is Empty" << endl;
        return;
    }

    //counting number of nodes in list and finding the last node in the list
    Country * tail = head; 
    int count = 0; 
    while (tail -> next != NULL)
    {
        tail = tail-> next; 
        count += 1;
    }


    if (end_index >= count || end_index < 0)
    {
        cout << "Invalid end index" << endl;
        return;
    }
    if (start_index > count || start_index < 0)
    {
        cout << "Invalid start index" <<endl;
        return;
    }
    if (start_index > end_index)
    {
        cout << "Invalid indices" << endl;
        return; 
    }
    
    //finding the node at the start index and getting the node that is right before it 
    Country * starter = head;
    Country *prev = NULL;
    int scounter =0;
    while (scounter < start_index)
    {
        prev  = starter;
        starter = starter -> next;
        scounter +=1; 
    }
    //finding the node that is at the end index
    Country * ender = head;
    int ecounter =0;
    while (end_index > ecounter)
    {
        ender = ender -> next;
        ecounter+=1;
    }
   if (prev == NULL)    //if head is the start index aka start index is 0 
    {
        head = ender -> next; //moving the head to the end 
    }
    else 
    {
        prev -> next = ender -> next; //the node right before the start index will point to what the end index used to be pointing to
    }
    tail -> next = starter;     //the last node in the list is going to the spot of the start index
    ender -> next = NULL;   //the node at the end index is now pointing to null

}
 

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    Country* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr->next != NULL)
        {
            cout << ptr->name << " -> ";
            ptr = ptr->next;
        }
        cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}
