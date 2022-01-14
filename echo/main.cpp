#include <iostream>
using namespace std;

int main() {

    string typedResponse = "";
    //char typedResponse[255];

    do {

        cout << "Please enter a line of text (Type 'end' to quit)" << endl;
        cin >> typedResponse;

        cout << "You entered the text: " + typedResponse + "\n" << endl;

    } while (typedResponse != "end");

    return 0;
}