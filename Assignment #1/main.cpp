//********************************************************************
//
// File: assignment1.cpp
// Author: Nolan Caissie
// Student number: 575384771
// Date: January 15th, 2017
// Updated: dates of changes to the file
//
// Purpose: The purpose of this assignment, is to use a linked list
// to record a number of food orders for a fast food chain.
//
// Notes: this is a doubly, circularly, linked list
// with a dummy node. The program will add nodes
// to the tail, enabling the program to visit
// the first node to display the oldest data in
// the list. when the user hits the "view" command
// the program will visit the front of the list (oldest data),
// traverse through next pointers, printing as it goes.
// when the user hits the "serve" command, the first (oldest),
// data will be visited, printed, and then deleted from the list.
// we will know once the list is empty because the dummy node
// will point to itself!!
//
// References: N/A
//********************************************************************
#include <string>
#include <iostream>
using namespace std;

//constants for order numbers mins and max
const int MinOrderNum = 100;
const int MaxOrderNum = 999;

//struct to hold data
struct Data {
    int orderNum;
    string burg;
    string side;
    string drnk;
};

//struct for a node
//points to data, next, and previous nodes
struct Node {
    Data *order;
    Node *prev;
    Node *next;
};

//function to create an empty list with a dummy node
//function will return a pointer to the node (head will
//point to this node)
Node *createEmptyList(){
    //make dummy's next and prev point to itself
    Node *ptr = new Node;
    ptr -> next = ptr;
    ptr -> prev = ptr;
    return ptr;
}

//function to check if the list is empty
//function will return true if it is.
bool isEmpty(Node *head){
    return (head -> next == head);
}

//function to add nodes to the tail
void addToTail(Node *head, Data *order){
    Node *ptr = new Node;
    //put new order into list
    ptr -> order = order;
    //connect circular link on last nodes next back to head
    ptr -> next = head;
    //make new node point to second last node in list
    ptr -> prev = head -> prev;
    //connect circular link on dummy's prev back to tail
    head -> prev = ptr;
    //make second last node point to last
    ptr -> prev -> next = ptr;
}

//remove from front function will display front
//then remove that node (will remove oldest data){
void removeFront(Node *head){
    if (head -> next != head) {
        cout << "Order Number: ";
        cout << head -> next -> order -> orderNum << endl;
        cout << "      Burger: ";
        cout << head -> next -> order -> burg << endl;
        cout << "        side: ";
        cout << head -> next -> order -> side << endl;
        cout << "       drink: ";
        cout << head -> next -> order -> drnk << endl;
        //cout << endl;

        //create victim pointer, make it point to front of list
        //(after dummy)
        Node *victim = head -> next;
        head -> next = victim -> next;
        head -> next -> prev = head;
        delete victim -> order;
        delete victim;
    //if the list is empty then delete the dummy
    } else if (head -> next == head){
        delete head;
    }
}

//display function (displays by traversal from head)
void display(Node *head){
    Node *ptr = head -> next;
    while (ptr != head) {
        cout << "Order Number: ";
        cout << ptr -> order -> orderNum << endl;
        cout << "      Burger: ";
        cout << ptr -> order -> burg << endl;
        cout << "        side: ";
        cout << ptr -> order -> side << endl;
        cout << "       drink: ";
        cout << ptr -> order -> drnk << endl;
        cout << endl;
        ptr = ptr -> next;
    }
    
}

//read order function taking in users input and returning
//a pointer to the data
Data *readOrder(int num){
    string restOfLine;
    Data *order = new Data;
    cout << "Please enter your choice for burger: ";
    cin.ignore();
    getline(cin, order -> burg);
    cout << "Please enter your choice for side-dish: ";
    getline(cin, order -> side);
    cout << "Please enter your choice for drink: ";
    getline(cin, order -> drnk);
    cout << "Your order number is " << num << endl << endl;
    order -> orderNum = num;
    return order;
}

//main routine
int main(){
    
    //create head with dummy node
    Node *listHead = createEmptyList();
    
    char userCommand = NULL;
    int orderNum = MinOrderNum;
    
    //introduction
    cout << "*** Welcome to Fast Food Ordering System ***" << endl << endl;
    cout << "Enter O to make a new order" << endl;
    cout << "or S to serve an order" << endl;
    cout << "or V to view all orders" << endl;
    cout << "or H for help (displays this menu)" << endl;
    cout << "or T to terminate this program" << endl << endl;
    
    //loop with conditions dependent on user command
    while (userCommand != 't' || userCommand != 'T') {
        
        cout << "------------------------------" << endl;
        cout << "Please enter your choice: ";
        cin >> userCommand;
        cout << "------------------------------";
        cout << endl << endl;
        
        
        //populate new order add to tail of list
        if (userCommand == 'o' || userCommand == 'O') {
            if (orderNum <= MaxOrderNum) {
                Data *ptr = readOrder(orderNum);
                addToTail(listHead, ptr);
                orderNum ++;
            } else {
                cout << "Fast Food Ordering System cannot hold more than";
                cout << MaxOrderNum - MinOrderNum << "orders." << endl;
                cout << "Please serve an order before trying to add another one." << endl <<endl;
            }
            
        //serve order: call display function then removeFront
        //to delete list
        } else if (userCommand == 's' || userCommand == 'S') {
            if (isEmpty(listHead)){
                cout << "Error: There are currently no orders in the system." << endl;
                cout << endl;
            } else {
            removeFront(listHead);
            cout << endl;
            }
        //view orders: call display if list not empty, otherwise display error
        } else if (userCommand == 'v' || userCommand == 'V') {
            if (isEmpty(listHead) == false) {
                display(listHead);
            } else {
                cout << "Error: There are currently no orders in the system." << endl << endl;
            }
            
        //help: display option menu
        } else if (userCommand == 'h' || userCommand == 'H') {
            cout << "Enter O to make a new order" << endl;
            cout << "or S to serve an order" << endl;
            cout << "or V to view all orders" << endl;
            cout << "or H for help (displays this menu)" << endl;
            cout << "or T to terminate this program" << endl << endl;
            
        //terminate: terminate the program if the list is NULL, otherwise display error
        } else if (userCommand == 't' || userCommand == 'T') {
            if (isEmpty(listHead) == false) {
                cout << "Error: there are currently orders in the system" << endl << endl;
            } else {
                cout << "The total number of orders processed is " << orderNum - MinOrderNum << endl;
                cout << endl;
                //delete dummy node
                removeFront(listHead);
                //end prog
                return 0;
            }
            
        }
        

    }
    
    
}
