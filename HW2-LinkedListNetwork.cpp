// ==========================================
// Created: September 16, 2016
// Sheila Doherty
// Homework Assignment #1
// Instructor: Elizabeth Boese
// Description: Linked List Fun
// ==========================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct city
{
    string 	name; 			// name of the city
    city 	*next; 			// pointer to the next city
	int 	numberMessages;	// how many messages passed through this city
    string 	message; 		// message we are sending accross
};

city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string filename);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
    // pointer to the head of our network of cities
    city *head = NULL;

	head = handleUserInput(head);
	printPath(head);
	head = deleteEntireNetwork(head);
	if (head == NULL)
		cout << "Path cleaned" << endl;
	else
		printPath(head);

	cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head the start of the linked list
 * @return the start of the linked list
 * Do NOT modify
 */
city* handleUserInput(city *head)
{
    bool quit = false;
    string s_input;
    int input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

		// read in input, assuming a number comes in
        getline(cin, s_input);
		input = stoi(s_input);

        switch (input)
        {
            // print all nodes
            case 1: 	//rebuild network
                head = loadDefaultSetup(head);
                printPath(head);
                break;

            case 2:		// print path
                printPath(head);
                break;

            case 3: //message is read in from file
			  {
        		string cityReceiver;
				cout << "Enter name of the city to receive the message: " << endl;
				getline(cin, cityReceiver);

				cout << "Enter the message to send: " << endl;
				string message;
				getline(cin, message);

                transmitMsg(head, cityReceiver, message);
			  }
                break;

            case 4:
			  {
        		string newCityName;
        		string prevCityName;
                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);

                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);

                // find the node containing prevCity
    			city *tmp = NULL;
                if(prevCityName !="First")
                    tmp = searchNetwork(head, prevCityName);
                // add the new node
                head = addCity(head, tmp, newCityName);
                printPath(head);
			  }
                break;

            case 5: 	// delete city
			  {
        		string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                head = deleteCity(head, city);
                printPath(head);
			  }
                break;

            case 6: 	// delete network
                head = deleteEntireNetwork(head);
                break;

            case 7: 	// quit
                quit = true;
				cout << "Quitting... cleaning up path: " << endl;
                break;

            default: 	// invalid input
                cout << "Invalid Input" << endl;
                break;
        }
    }
	return head;
}

/*
 * Purpose: Add a new city to the network
 *   between the city *previous and the city that follows it in the network.
 * @param head pointer to start of the list
 * @param previous name of the city that comes before the new city
 * @param cityName name of the new city
 * @return pointer to first node in list
 */

city* addCity(city *head, city *previous, string cityName ) //received help from http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C
{//received help from Mckenzi in the CSEL lab
    //add to start of list
    city *newCity = new city;
    newCity->name = cityName;
    city *tempCity = NULL;

    if (head == NULL) //the first time a new node is added
    {
        newCity->next = NULL;
        head = newCity;
    }
    else if (head != NULL && previous == NULL) //adds a new node to the start of the list
    {
        tempCity = head;
        newCity->next = tempCity;
        head = newCity;
    }
    else if (previous->next == NULL) //adds a new node to the end of a list
    {
        newCity->next = NULL;
        previous->next = newCity;
        cout << "prev: " << previous->name << "  new: " << cityName << endl;
    }
    else if (previous -> next != NULL) //adds a new node in the middle of a list
    {
        newCity->next = previous->next;
        previous->next = newCity;
        cout << "prev: " << previous->name << "  new: " << cityName << endl;
    }
    return head;
}


/*
 * Purpose: Search the network for the specified city and return a pointer to that node
 * @param ptr head of the list
 * @param cityName name of the city to look for in network
 * @return pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
city *searchNetwork(city *ptr, string cityName)
{
    city *tmp;
    tmp = ptr;
    while (tmp->next && tmp->name !=cityName) //cycles through the list until cityName is found
    {
        tmp = tmp->next;
    }
    ptr = tmp;
    return ptr;
}

/*
 * Purpose: deletes all cities in the network starting at the head city.
 * @param ptr head of list
 * @return NULL as the list is empty
 */
city* deleteEntireNetwork(city *ptr)
{
    while (ptr != NULL)
    {
        cout << "deleting: " << ptr->name << endl;
        city *temp = ptr;
        ptr = temp -> next; // from the head on through the list, each item is deleted one-by-one
        delete temp;
    }

	cout << "Deleted network" << endl;
    // return head, which should be NULL
    return ptr;
}

/* sends messages from file */
void transmitMsg(city *head, string receiver, string message)
{
    city *sender = new city;
    sender = head;

    if(head == NULL)
	{
        cout << "Empty list" << endl;
        return;
    }
    else
    {
        while (sender && sender->name != receiver) //cycles through the list until receiver is found
        { //along the way it increments the number of messages it has received
            sender->message = message;
            sender->numberMessages = sender->numberMessages + 1;
            cout << sender->name << " [# messages passed: " << sender->numberMessages << "] received: " << sender->message << endl;
            sender = sender->next;
        }
        //once the receiver is found, the message is passed
        sender->message = message;
        sender->numberMessages = sender->numberMessages +1;
        cout << sender->name << " [# messages passed: " << sender->numberMessages << "] received: " << sender->message << endl;
    }
}


/*
 * Purpose: delete the city in the network with the specified name.
 * @param head first node in list
 * @param cityName name of the city to delete in the network
 * @return head node of list
 */
city* deleteCity(city *head, string cityName)
{
    city *temp = new city;
    temp = head;
    city *prevCity = new city;
    prevCity = head;

    while (temp->name != cityName) //cycles through the list until cityName is found
    {
        prevCity = temp;
        temp = temp->next;
    }
    if (prevCity == head) //if prevCity still == head, then head is set to next list item
    {
        head = temp->next;
        delete temp;
    }
    else
    {
        prevCity->next = temp->next; //sets the previous->next to the temp->, and removes the city
        delete temp;
    }
    return head;
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void printPath(city *ptr)
{
    city *listPrinter = new city;
    listPrinter = ptr;

    cout << "== CURRENT PATH ==" << endl;

    // If the head is NULL
    if (ptr == NULL)
    {
        cout << "nothing in path" << endl;
    }
    else
    {
       while (listPrinter) //cycles through the list until NULL is reached, printing out each name
       {
            cout << listPrinter->name << " -> ";
            listPrinter = listPrinter->next;
       }
       cout << "NULL" << endl;
    }
    cout << "===" << endl;
    delete listPrinter;
}

/*
 * Purpose: populates the network with the predetermined cities
 * @param head start of list
 * @return head of list
 */
city* loadDefaultSetup(city *head)
{
    head = deleteEntireNetwork(head);
    head = addCity(head,NULL,"Los Angeles");

	city *temp;
	temp = searchNetwork(head, "Los Angeles"); //searches for city and returns it's pointer
    head = addCity(head, temp, "Phoenix"); //uses the pointer from the search as previous to add another city

	temp = searchNetwork(head, "Phoenix");
	head = addCity(head, temp, "Denver");

	temp = searchNetwork(head, "Denver");
    head = addCity(head, temp, "Dallas");

	temp = searchNetwork(head, "Dallas");
	head = addCity(head,temp, "Atlanta");

	temp = searchNetwork(head, "Atlanta");
	head = addCity(head,temp, "New York");

    cout << "Load Default Setup end" << endl;

    return head;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
	cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Delete City" << endl;
    cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}

