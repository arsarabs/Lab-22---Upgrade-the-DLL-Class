#include <iostream>
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
    srand(static_cast<unsigned int>(time(0))); //Seed Generation
    DoublyLinkedList list; //Linked List Instance 

    //MAIN ROUGH LAYOUT BELOW
    
    //#1: Determine and display random initial size 
    int initial_size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    cout << "Initializing list with " << initial_size << " random elements between " << MIN_NR << " and " << MAX_NR << endl;

    //#2: Populate the list with random numbers
    for (int i = 0; i < initial_size; ++i) {
        int value = rand() % (MAX_NR - MIN_NR + 1) + MIN_NR; 
        list.push_back(value); // insert random val at end of list
    }
    list.print();          // Display the list from head to tail
    list.print_reverse();  // Display the list from tail to head
    cout << "List size: " << list.size() << endl; // Output the current size of the list

    //#3: Adding elements to front/back
    cout << "Add 42 to front " << endl;
    list.push_front(42);
    cout << "Add 24 to back " << endl;
    list.push_back(42);

    //#4: Inserting after invalid position
    int invalid_pos = 247;
    cout << "Tried to insert 25 after invalid position " << invalid_pos << endl;
    list.insert_after(25, invalid_pos);
    
    //#5: Inserting after valid position
    int insert_pos = 4;   //positon
    int insert_val = 48;  // Value inserted
    cout << "Inserting " << insert_val << " after position " << insert_pos << endl;
    list.insert_after(insert_val, insert_pos);
    
    //#6: Deletion of existing/nonexisting values
    
    //#7: Deletion by position
    
    //#8: Popping front/back
    
    
    //#9: Clear List



    

    return 0;
}
