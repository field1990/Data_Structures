#include <iostream>
#include <iomanip>

using namespace std;

class Node;//Put declaration before so that Node* is known before to redefine it

typedef Node* NodePtr; //Giving Mode*, a known type, a new name, an alias

class Node{

public:
    int m_data {-1};
    NodePtr m_left {nullptr};
    NodePtr m_right {nullptr};
};

class BST {

private:
    NodePtr m_root {nullptr};

public:
    //Rercursive insert
    void insert(int num){
        //entry point
        insert(num, m_root);
    }

    //First Scenario
    void remove(int num){

        NodePtr node = m_root;
        NodePtr parent = nullptr;

        //Finding the node, loop while the node does not equal null
        while(node != nullptr){
            if(num < node->m_data){
                //Go to the left is node is less than the nodes value
                parent = node;
                node = node->m_left;
            } else if (num > node->m_data){
                //Go to the right
                parent = node;
                node = node->m_right;
            } else {
                //Found the node!
                break;
            }
        }

        // If node is equal to null, couldn't find the node, exit if node was not found
        if(node == nullptr) return;

        //Find a successor, if the node has two children
        if (node->m_left != nullptr && node->m_right != nullptr){
            //Start at the left subtree
            NodePtr successor = node->m_left;

            //Now go right as far as possible to replace the parent with the furthers right node to the left of the parent
            parent = node;
            while (successor->m_right != nullptr){
                //When we hit this we now this success is thr right most node
                //Set this node to be equal to the parent
                parent = successor;
                //
                successor = successor->m_right;
            }

            //Swap values with the sucessor
            node->m_data = successor->m_data;
            //Delete the old successor later on
            node = successor;
        }

        //Have to keep track of where parent is and the child is located with relation to the parent
        //Do we have any children?
        NodePtr subtree = node->m_left;
        if(subtree == nullptr){
            //there are no children on the left side
            //subtree will be a valid pointer to the right or null if there are no children
            subtree = node->m_right;
        }

        // Which side are we connected to?
        if (parent == nullptr) {
            m_root = subtree;
        } else if (node == parent->m_left) {
            parent->m_left = subtree;
        } else if (node == parent->m_right){
            parent->m_right = subtree;
        }

        //Finally, delete the node
        delete node;
    }

    void save_array(int* array){
        save_array(array, m_root);
    }

protected:
    //Recurive insert for others beside the start
    void insert(int num, Node*& node){ //Reference to a Node pointer, want to modify that reference
        if (node == nullptr){
            node = new Node();
            node->m_data = num;
        } else if (num < node->m_data) {
            //Go to the left side
            insert(num, node->m_left);
        } else if (num > node->m_data) {
            //Go to the right side
           insert(num, node->m_right);
        } else {
            //Trying to insert node of duplicate value
            cout << "Node value " << node->m_data << " already exists." << endl;
        }
    }

    void save_array(int* array, NodePtr node){
        // Position in the array to store value
        //Sorta like a global variable, protected, local to the function, can't access this variable outside of this function, scoped more than global
        //Static will retain the value in the variable even in separate function calls
        static int i = 0;

        if(node != nullptr){
            save_array(array, node->m_left);
            array[i++] = node->m_data;
            save_array(array, node->m_right);
        }
    }

    void PrintTree(ostream& output, NodePtr& node, int indent) {
        if (node != nullptr) {
            PrintTree(output, node->m_right, indent + 8); //Indenting by 8 spaces, it could be any number, just to make it look good
            output <<setw(indent) << node->m_data << endl; //Set the width with setw, import iomanip
            PrintTree(output, node->m_left, indent + 8);
        }

    }

    friend ostream& operator<<(ostream& output, BST& bst);
};

ostream& operator<<(ostream& output, BST& bst) {
    bst.PrintTree(output, bst.m_root, 0);
    return output;
}

//Printing out contents of array
void dump_array(int* array, int len) {
    for(int i = 0; i < len; i++){
        cout << setw(3) << array[i];
    }
    cout << endl;
}

void bst_sort(int* array, int len){

    BST bst;

    for (int i = 0; i < len; i++){
        bst.insert(array[i]);
    }

    bst.save_array(array);
}

int main() {

    int nums[] = {3, 6, 8, 10, 5, 9, 4, 7, 1, 2};
    int len = sizeof(nums)/sizeof(int);

    cout << "Before Sorting..." << endl;
    dump_array(nums, len);

    bst_sort(nums, len);

    cout << "After Sorting..." << endl;
    dump_array(nums, len);

    return 0;
}