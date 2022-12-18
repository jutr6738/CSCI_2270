/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{ // points to the first node in the linked list 
    Country *head= NULL;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    if (head==NULL) //there is no linked list, there is only head 
    {
        head = new Country; //there is no head so we are making a head 
        head -> name = countryName;
        head -> next = NULL;

        cout << "adding: " << countryName << " (HEAD)" << endl; 
    }
    else if (previous == NULL)  //adding before head 
    {
        Country *newCountry = new Country;  //creating new country
        newCountry -> name = countryName; //storing the country name
        newCountry -> next = head;  //making our new country point to the head aka new country points to null  
        head = newCountry;  //now we are switching it so head points to the new country so we make head come first

        cout << "adding: " << countryName << " (HEAD)" << endl; 
    }
    else
    {
        Country *newCountry= new Country;
        newCountry -> name = countryName;
        newCountry -> next = previous -> next; //now new country points to what the one before it was 
        previous -> next = newCountry; //now the previous country points to what I just inserted 
        
        cout << "adding: " << countryName << " (prev: " << previous -> name << ")" <<endl;
    }

}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    insertCountry(NULL, "United States");
    insertCountry(searchNetwork("United States"), "Canada");
    insertCountry(searchNetwork("Canada"), "Brazil");
    insertCountry(searchNetwork("Brazil"), "India");
    insertCountry(searchNetwork("India"), "China");
    insertCountry(searchNetwork("China"), "Australia");
    searchNetwork("Australia") -> next = NULL; 
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    Country * searcher= head;   //since searcher is initialized to head 

    while (searcher != NULL && searcher -> name != countryName) //we want to stop at the end of the list (null) or at the country name
    { 
        searcher = searcher -> next; //traversing through the array. 
    }

    return (searcher);
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    
    Country * transmitter = head;
    if (head == NULL)
    {
        cout << "Empty List" << endl;
    }

    else if (searchNetwork(receiver) == NULL)    //making sure that the receiver is in the list
    {
        cout << "Country not found" << endl;
    }
    else //since the reciever is in the list, we will loop through the list and send the message to all the countries until we get to the reciever 
    {
        while (transmitter->name != receiver) 
        { 
            transmitter-> message = message;    //setting the transmitter's message equal to the message 
            transmitter -> numberMessages += 1; //incrementing number of messages 

            cout << transmitter-> name << " [# messages received: " << transmitter -> numberMessages << "] received: " << transmitter-> message << endl;
            
            transmitter = transmitter -> next; //traversing through the array. 
        }
        //now we need to send the message to the receiver 
        transmitter-> message = message;    
        transmitter -> numberMessages += 1; 
        cout << transmitter-> name << " [# messages received: " << transmitter -> numberMessages << "] received: " << transmitter-> message << endl;

    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
    Country * printer= head; 

    cout << "== CURRENT PATH ==" <<endl;

    if (head== NULL)
    {
        cout << "nothing in path" << endl;
    }

    else 
    {
        while (printer->next != NULL)
        {
            cout << printer -> name << " -> ";
            printer = printer -> next;
        }
        cout << printer -> name << " -> " << "NULL" << endl;
    }
    cout << "===" <<endl;
}
