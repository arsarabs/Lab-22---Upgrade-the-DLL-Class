
#include <iostream>
#include <iomanip>  
#include <cstdlib>  
#include <ctime>    
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// //#1: DoublyLinkedList Class Definition
class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        // Constructor for Node
        Node(int val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
    };

    Node* head;
    Node* tail;
    

public:
    //#2: Constructor
     // DoublyLinkedList() initializes an empty list
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //#3: Destructor
 // ~DoublyLinkedList() cleans up all nodes to prevent memory leaks
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    //#6: insert_after() inserts a node after a specified position
// arguments: int value - the data to be inserted
//            int position - the position after which to insert the new node
// returns: void

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* temp = head; // Start traversal from the head of the list

        // Traverse the list to reach the specified position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Error: Position " << position << " exceeds list size. Node not inserted." << endl;
            return;
        }

        // Create a new node with the given value
        // The new node's prev points to temp, and next points to temp's next
        Node* newNode = new Node(value, temp, temp->next);
        
        if (temp->next){ // If temp is not the last node
            temp->next->prev = newNode;
        }
        else {
            tail = newNode; // If temp was the tail, update tail to the new node
            temp->next = newNode;  // Link temp's next to the new node
        }

        cout << "Inserted value " << value << " after position " << position << "." << endl;
    }
    //#7: delete_val() deletes the first node with the specified value
    // arguments: int value - the data to be deleted from the list
    // returns: void
    void delete_val(int value) {
        if (!head) { // If the list is empty
            cout << "Error: List is empty. Cannot delete value " << value << "." << endl;
            return;
        }

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) { // If the value is not found in the list
            cout << "Error: Value " << value << " not found in the list." << endl;
            return;
        }

        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void delete_pos(int position) {
        if (position < 0) { // Validate that position is non-negative
            cout << "Error: Position must be >= 0." << endl;
            return;
        }

        if (!head) { // If the list is empty
            cout << "Error: List is empty. Cannot delete position " << position << "." << endl;
            return;
        }

        Node* temp = head; // Start traversal from the head

        // Traverse the list to reach the specified position
        for (int i = 0; i < position && temp; ++i) {
            temp = temp->next;
        }

        if (!temp) { // If the position exceeds the list size
            cout << "Error: Position " << position << " exceeds list size. No node deleted." << endl;
            return;
        }

        if (temp->prev) { // If the node to delete is not the head
            temp->prev->next = temp->next; // Link the previous node's next to the current node's next
        }
        else {
            head = temp->next; // If deleting the head, update head to the next node
        }

        if (temp->next) { // If the node to delete is not the tail
            temp->next->prev = temp->prev; // Link the next node's prev to the current node's prev
        }
        else {
            tail = temp->prev; // If deleting the tail, update tail to the previous node
        }
         
        cout << "Deleted node at position " << position << " with value " << temp->data << "." << endl;
        delete temp; // Delete the node to free memory
    }
     
    //#9: pop_front() removes the head node from the list
   // arguments: none
   // returns: void

    void pop_front() {
        //check for empty list
        if (!tail) {
            cout << "List EMPTY" << endl;
            return;
        }
        //Create a temp ptr to the current head
        Node* temp = head;

        //If there's more than one more node, update head to previous node OR set head/tail to nullptr
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else {
            head = tail = nullptr;
        }
        cout << "Popped FRONT node " << temp->data << endl;
        delete temp; //free memory
    }

   


     //#10: pop_back() removes the tail node from the list
    // arguments: none
    // returns: void

    void pop_back() {
        //check for empty list
        if (!tail) {
            cout << "List EMPTY" << endl;
            return;
        }
        //Create a temp ptr to the current tail
        Node* temp = tail;

        //If there's more than one more node, update tail to previous node OR set head/tail to nullptr
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            head = tail = nullptr;
        }
        cout << "Popped BACK node " << temp->data << endl;
        delete temp; //free memory
    }


    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    //#13: size() returns the current number of nodes in the list
      // arguments: none
      // returns: int - size of the list
    int size() const {
        int count = 0;           // Initialize a counter for the number of nodes
        Node* current = head;    // Start from the head of the list

        // Traverse the list and count each node
        while (current) {
            ++count;               // Increment the counter
            current = current->next; // Move to the next node
        }

        return count; // Return the total count of nodes
    }

}; 

// Driver program
int main() {
    cout << "Upgraded the DLL Class: " << endl;
    cout << "**********************************************************************************************" << endl;
    cout << endl;

    srand(static_cast<unsigned int>(time(0))); //Seed Generation
    DoublyLinkedList list; //Linked List Instance 

   
    //#1: Determine and display random initial size 
    int initial_size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    cout << left << setw(50) << "Initializing list with " << initial_size << " random elements between " << MIN_NR << " and " << MAX_NR << endl;

    //#2: Populate the list with random numbers
    for (int i = 0; i < initial_size; ++i) {
        int value = rand() % (MAX_NR - MIN_NR + 1) + MIN_NR; 
        list.push_back(value); // insert random val at end of list
    }
    //DISPLAY CURRENT STATUS OF LIST
    cout << "**********************************************************************************************" << endl;
    cout << left << setw(50) << "List forward:";
    list.print();          // Display the list from head to tail
    cout << left << setw(50) << "List backward:";
    list.print_reverse();  // Display the list from tail to head
    cout << left << setw(50) << "List size: " << list.size() << endl; // Output the current size of the list

    //#3: Adding elements to front/back
    cout << endl;
    cout << left << setw(50) << "Add 42 to front" << endl;
    list.push_front(42);
    cout << left << setw(50) << "Add 24 to back" << endl;
    list.push_back(24);

    //#4: Inserting after invalid position
    cout << endl;
    int invalid_pos = 247;
    cout << left << setw(50) << "Tried to insert 25 after invalid position " << invalid_pos << endl;
    list.insert_after(25, invalid_pos);
    
    //#5: Inserting after valid position
    cout << endl;
    int insert_pos = 4;   //positon
    int insert_val = 48;  // Value inserted
    cout << left << setw(50) << "Inserting " << insert_val << " after position " << insert_pos << endl;
    list.insert_after(insert_val, insert_pos);

    //DISPLAY CURRENT STATUS OF LIST
    cout << "**********************************************************************************************" << endl;
    cout << left << setw(50) << "List forward:";
    list.print();          // Display the list from head to tail
    cout << left << setw(50) << "List backward:";
    list.print_reverse();  // Display the list from tail to head
    cout << left << setw(50) << "List size: " << list.size() << endl; // Output the current size of the list

    //#6: Deletion of existing/nonexisting values
    cout << endl;
    int delete_val = 31;
    cout << left << setw(50) << "Deleting the value " << delete_val << endl;
    list.delete_val(delete_val);

    int delete_non = 31;
    cout << left << setw(50) << "Tried to delete " << delete_val << endl;
    list.delete_val(delete_non);

    //DISPLAY CURRENT STATUS OF LIST
    cout << "**********************************************************************************************" << endl;
    cout << left << setw(50) << "List forward:";
    list.print();          // Display the list from head to tail
    cout << left << setw(50) << "List backward:";
    list.print_reverse();  // Display the list from tail to head
    cout << left << setw(50) << "List size: " << list.size() << endl; // Output the current size of the list
    
    //#7: Deletion by position
    cout << endl;
    int invalid_delete_pos = 74; //Invalid Attempt
    cout << left << setw(50) << "Tried to delete node at invalid position " << invalid_delete_pos << endl;
    list.delete_pos(invalid_delete_pos);

    int delete_position = 2; //Valid
    cout << left << setw(50) << "Deleting node at position " << delete_position << endl;
    list.delete_pos(delete_position); // delete node @ position 2 within list

    //DISPLAY CURRENT STATUS OF LIST
    cout << "**********************************************************************************************" << endl;
    cout << left << setw(50) << "List forward:";
    list.print();          // Display the list from head to tail
    cout << left << setw(50) << "List backward:";
    list.print_reverse();  // Display the list from tail to head
    cout << left << setw(50) << "List size: " << list.size() << endl; // Output the current size of the list

    //#8: Popping front/back
    cout << endl;
    cout << left << setw(50) << "Popping FRONT node" << endl;
    list.pop_front(); 

    cout << left << setw(50) << "Popping the BACK node" << endl;
    list.pop_back(); 

    //DISPLAY CURRENT STATUS OF LIST
    cout << "**********************************************************************************************" << endl;
    cout << left << setw(50) << "List forward:";
    list.print();          // Display the list from head to tail
    cout << left << setw(50) << "List backward:";
    list.print_reverse();  // Display the list from tail to head
    cout << left << setw(50) << "List size: " << list.size() << endl; // Output the current size of the list
    
    //#9: Clear List
    cout << endl;
    cout << left << setw(50) << "CLEAR LIST" << endl;
    //Use a simple while loop to remove nodes until list is empty
    while (list.size() > 0) {
        list.pop_front();
    }

    //DISPLAY CURRENT STATUS OF LIST
    cout << "**********************************************************************************************" << endl;
    cout << left << setw(50) << "List forward:";
    list.print();          // Display the list from head to tail
    cout << left << setw(50) << "List backward:";
    list.print_reverse();  // Display the list from tail to head
    cout << left << setw(50) << "List size: " << list.size() << endl; // Output the current size of the list
   

    return 0;
}
