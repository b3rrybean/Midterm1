#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;       // The integer data stored in this node
        Node* prev;     // Pointer to the previous node
        Node* next;     // Pointer to the next node

        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
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
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {    // Empty list
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {    // Position out of bounds
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

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
        if (!head) return;

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return;      // Value not found

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;  // Removing head

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;  // Removing tail

        delete temp;
    }

    // Delete node by position
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            } else
                temp = temp->next;
        }

        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {      // Last node
            pop_back();
            return;
        }

        // Remove temp from list
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
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
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Prints all nodes from head to tail
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;            // Move forward in the list
        }
        cout << endl;
    }

    // Print all elements from tail to head
    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // New mothod: print every other element (starting with first)

    
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    return 0;
}
