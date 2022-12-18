/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	string input; 
	ProducerConsumer pc= ProducerConsumer(); 

	
	while (input!= "3")
	{
		menu();
		getline(cin, input);

		if (input=="1")
		{
			int numItems; 

			cout << "Enter the number of items to be produced:" << endl;
			getline(cin, input);
			numItems= stoi(input);

			int i=1;
			while (i<=numItems)
			{
				cout << "Item" << i << ":" << endl;
				getline(cin, input);
				pc.enqueue(input);
				i++;
			}
		}
		else if (input=="2")
		{
			int numItems; 

			cout << "Enter the number of items to be consumed:" << endl;
			getline(cin, input);
			numItems= stoi(input);

			int i=1;
			while (i<=numItems)
			{
				if (pc.isEmpty())
				{
					cout << "No more items to consume from queue" << endl;
					break; 
				}
				else {
					cout << "Consumed: " << pc.peek() << endl;
					pc.dequeue();
				}
				i++;
			}
		}
		else if (input=="3")
		{

			cout << "Number of items in the queue:" << pc.queueSize() << endl;
			return 0;
		}
	}

}
