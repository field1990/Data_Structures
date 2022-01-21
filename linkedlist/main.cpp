#include <iostream>
#include <memory>

using namespace std;

class LinkedListNode{
public:
    int m_data;             // the data to store (could be anything)
    LinkedListNode* m_next; // a pointer to the next node in the chain

    LinkedListNode() : m_data(-1), m_next(nullptr) {} //constructor
};

class LinkedList {
private:
    LinkedListNode* m_start; // points to the first node in the chain
    int m_size;

public:
    LinkedList() : m_start(nullptr), m_size(0) {} // constructor
    virtual ~LinkedList(){
        LinkedListNode* node = m_start;

        while (node != nullptr){

            //Temporary pointer to keep track of node
            LinkedListNode* temp = node;
            node = node->m_next;

            delete temp;
        }

        //delete m_start;

    }

    void add(int data){ //just adding on to the node

        //create a new node
        LinkedListNode* new_node = new LinkedListNode();

        //smart pointer version?
        //auto new_node = make_unique<LinkedList>();
        new_node->m_data = data;

        // add the first node to the chain
        // look to see if there's a node in the chain first
        // is this the first node in the chain?
        if (m_start == nullptr){
            // add the first node to the chain
            m_start = new_node;
        } else {
            // adding nodes to the end of an existing chain
            LinkedListNode* node = m_start;
            LinkedListNode* prev = nullptr;

            // Look for the node with a null "next" pointer
            while (node != nullptr){
                prev = node;
                node = node->m_next;
            }

            // Once at the end of the chain attach new node to the end of the chain
            if (prev != nullptr){
                prev->m_next = new_node;
            }
        }
        m_size++;
    }

    void insert_node(int data, int position){

        //Check to see if there is at least one node to insert before
        if (position > m_size){
            cout << "Node to insert before doesn't exist." << endl;
            return;
        }

        LinkedListNode* new_node = new LinkedListNode();
        //did we allocate some memory for the new node?
        if (new_node == nullptr){
            cout << "Couldn't allocate memory for new nodes." << endl;
            return;
        }
        new_node->m_data = data;

        //Find position
        LinkedListNode* node = m_start;
        LinkedListNode* prev = nullptr;

        int current_position = 1;

        while (node != nullptr){

            //Application specific - use position to find node
            if (current_position == position){
                break;
            }

            current_position++;

            prev = node;
            node = node->m_next;
        }

        if (prev == nullptr) {
            // insert node at the start
            new_node->m_next = m_start;
            m_start = new_node;

        } else {

            // insert node in the middle
            new_node->m_next = prev->m_next;
            prev->m_next = new_node;

        }

        m_size++;
    }

    void delete_node(int data){

        LinkedListNode* node = m_start;
        LinkedListNode* prev = nullptr;

        // find the node to delete
        while (node != nullptr){

            // logic to find the node
            if (node->m_data == data){
                break;
            }

            prev = node;
            node = node->m_next;
        }

        // did I find the node to delete?
        if (node != nullptr){

            // am I deleting the first node? or a different node?
            if (prev == nullptr){ //or node == m_start

                // we're deleting the first node
                m_start = node->m_next;

            } else{
                // must be a different node!
                prev->m_next = node->m_next;

            }

            delete node;
            m_size--;
        }
    }

    friend ostream& operator<<(ostream& output, LinkedList& list);

};

ostream& operator<<(ostream& output, LinkedList& list){

    LinkedListNode* node = list.m_start; //start with the first node

    // Output the data from all the nodes in the chain
    while (node != nullptr){
        cout << node->m_data <<  " ";
        node = node->m_next;
    }

    return output;
}

int main() {

    LinkedList list;

    // test 1 - add new nodes
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    cout << "Test 1" << endl;
    cout << "------" << endl;
    cout << list << endl;

    // test 2 - deleting node in the middle
    list.delete_node(3); //delete the node with the value of 3

    cout << "Test 2" << endl;
    cout << "------" << endl;
    cout << list << endl;

    // test 3 - deleting node at the end
    list.delete_node(5); //delete the node with the value of 5

    cout << "Test 3" << endl;
    cout << "------" << endl;
    cout << list << endl;

    // test 4 - deleting node at the beginning
    list.delete_node(1); //delete the node with the value of 1

    cout << "Test 4" << endl;
    cout << "------" << endl;
    cout << list << endl;

    // test 5 - inserting in the middle of the list
    list.insert_node(6, 2); //Insert 6 before node number 2

    cout << "Test 5" << endl;
    cout << "------" << endl;
    cout << list << endl;

    // Test 6 - insert at the beginning of the list
    list.insert_node(7, 1); // insert 7 before node number 1

    cout << "Test 6" << endl;
    cout << "------" << endl;
    cout << list << endl;

    // Test 7 - try to insert into empty list
    cout << "Test 7" << endl;
    cout << "------" << endl;

    LinkedList list2;
    list2.insert_node(10, 1); // try to insert 10 before node 1

    cout << list2 << endl;

    return 0;
}