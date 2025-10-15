#include <iostream>
using namespace std;

// Constraints for min/max values (previously used in dummy statement)
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    // Node struct represents each element in the doubly linked list
    struct Node {
        int data;       // The integer data stored in this node
        Node* prev;     // Pointer to the previous node
        Node* next;     // Pointer to the next node

        // Node constructor initializes the data and optional previous/next pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // Set the node's data
            prev = p;   // Set the pointer to previous node
            next = n;   // Set pointer to next node
        }
    };

    Node* head;         // Pointer to the first node (front of the list)
    Node* tail;         // Pointer to the last node (end of the list)

public:
    DoublyLinkedList() {
        // Initializes pointers to null (empty list)
        head = nullptr;
        tail = nullptr;
    }

    // Insert a node after a specific position
    void insert_after(int value, int position) {
        if (position < 0) {     // Check for invalid position
            cout << "Position must be >= 0." << endl;
            return;
        }

        // Create a new node with value
        Node* newNode = new Node(value);

        // If empty, both head and tail point to new node
        if (!head) {    // Empty list
            head = tail = newNode;
            return;
        }

        // Start from the head to find the target position
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;  // Move forward in the list

        if (!temp) {            // Position out of bounds
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // Link newNode into the list
        newNode->next = temp->next;     // New node points to next node
        newNode->prev = temp;           // New node points back to temp

        if (temp->next)
            temp->next->prev = newNode; // Next node points back to new node
        else
            tail = newNode;             // If at end, update tail

        temp->next = newNode;           // Temp points forward to new node
    }


    // Delete node by value
    void delete_val(int value) {

        // If empty, nothing to delete
        if (!head) return;

        // Start from head
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;  // Traverse list to find value

        if (!temp) return;      // Value not found

        // Update pointers to remove node
        if (temp->prev)
            temp->prev->next = temp->next;  // Previous node skips over temp
        else
            head = temp->next;  // If deleting head, update head

        if (temp->next)
            temp->next->prev = temp->prev;  // Next node skips over temp
        else
            tail = temp->prev;  // If deleting tail, update tail

        delete temp;
    }

    // Delete node by position (1-based indexing)
    void delete_pos(int pos) {
        if (!head) {    // Check if list is empty
            cout << "List is empty." << endl;
            return;
        }

        // Special case: delete first node
        if (pos == 1) {
            pop_front();
            return;
        }

        // Start from head
        Node* temp = head;
        for (int i = 1; i < pos; i++) { // Move to the target position
            if (!temp) {                // Position doesn't exist
                cout << "Position doesn't exist." << endl;
                return;
            } else
                temp = temp->next;      // Move forward
        }

        if (!temp) {            // Extra safety check
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {      // Special case: delete last node
            pop_back();
            return;
        }

        // Normal case: remove temp from the middle
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;    // Link previous node to next
        temp->next->prev = tempPrev;    // Link next node back to previous
        delete temp;                    // Free memory
    }

    // Adds a new node to the end of the list
    void push_back(int v) {
        Node* newNode = new Node(v);

        // If empty, both head and tail point to new node
        if (!tail)
            head = tail = newNode;

        // Otherwise, link after tail
        else {
            tail->next = newNode;           // New node points forward to old head
            newNode->prev = tail;           // Old head points backward to new node
            tail = newNode;                 // Update head pointer to new node
        }
    }

    // Adds a new node to the front of the list
    void push_front(int v) {
        // Create a new node with data = value
        Node* newNode = new Node(v);

        // If the list is empty, head and tail both point to the new node
        if (!head)
            head = tail = newNode;
        
        // Otherwise, link new node before current head
        else {
            newNode->next = head;           // New node points forward to old head
            head->prev = newNode;           // Old head points backward to new node
            head = newNode;                 // Update head pointer to new node
        }
    }


    // Removes the first node in the list
    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        // Temporarily store the node being removed
        Node* temp = head;

        // If only one node exists, both head and tail become null
        if (head->next) {
            head = head->next;
            head->prev = nullptr;

        // Otherwise, move head forward and clear the previous link
        } else
            head = tail = nullptr;

        // Free memory
        delete temp;
    }

    // Removes the last node in the list
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }

        // Temporarily store the node being removed
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;

        // Otherwise, move tail pointer backward and clear next link
        } else
            head = tail = nullptr;

        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {              // While list is not empty
            Node* temp = head;      // Save current head
            head = head->next;      // Move head forward
            delete temp;            // Delete old head
        }
    }

    // Prints all nodes from head to tail
    void print() {
        Node* current = head;       // Start at head
        if (!current) {             // Empty list check
            cout << "List is empty." << endl;
            return;
        }
        while (current) {           // Traverse list
            cout << current->data << " ";       // Print current node
            current = current->next;            // Move forward in the list
        }
        cout << endl;
    }

    // Print all elements from tail to head
    void print_reverse() {
        Node* current = tail;                   // Start at tail
        if (!current) {                         // Empty list check
            cout << "List is empty." << endl;
            return;
        }
        while (current) {                       // Traverse backward
            cout << current->data << " ";
            current = current->prev;            // Move backward
        }
        cout << endl;
    }

    // New mothod: print every other element (starting with first)
    void every_other_element() {
        if (!head) {    // Empty list check
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;   // Start at head
        bool skip = false;      // Whether or not to skip node

        cout << "Every other element: ";
        while (current) {       // Traverse list
            if (!skip)          // Print if not skipping
                cout << current->data << " ";
            skip = !skip;       // Flip skip flag
            current = current->next;    // Move forward
        }
        cout << endl;
    }

};

int main() {
    DoublyLinkedList list;

    // Test data
    list.push_back(20);
    list.push_back(40);
    list.push_back(60);
    list.push_back(80);
    list.push_back(100);

    // Test every_other_element
    list.every_other_element();     // Should print 20 60 100

    cout << "Forward: ";
    list.print();         // Should print 20 40 60 80 100

    cout << "Reverse: ";
    list.print_reverse(); // Should print 100 80 60 40 20

    list.delete_val(60);
    cout << "After deleting 60: ";
    list.print();         // Should print 20 40 80 100

    list.delete_pos(2);
    cout << "After deleting position 2: ";
    list.print();         // Should print 20 80 100

    list.pop_front();
    list.pop_back();
    cout << "after popping front and back: ";
    list.print();         // Should print 80

    return 0;
}
