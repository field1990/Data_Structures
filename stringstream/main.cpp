#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int main() {

    char input[256];
    char command[256];
    //int start, end;

    cout << "Enter some text: ";
    cin.getline(input, 256);

    // add a stringstream //an internal buffer, can put the input in that stringstream and go through it
    stringstream ss;
    ss << input;

    ss >> command;

    // any text more than a single character
    // we will assume to be text, not a command
    if (strlen(command) > 1){
        cout << "You entered some text." << endl;
    } else {
        cout << "I think you entered a command." << endl;


        int start = -1;
        int end = -1;
        ss >> start;
        if ((ss.fail())){
            ss.clear();
            cout << "No start number exists." << endl;

            // if no number, is there anything?
            ss >> command;
            if (ss.fail()){
                cout << "No text either." << endl;
            } else {
                cout << "Must actually be text instead of a command." << endl;
            }
        } else {

            //int end = -1;
            ss >> end;
            if (ss.fail()){
                cout << "There was no ending number" << endl;
            }
        }


        cout << "command: " << command;
        cout << ", start: " << start;
        cout << ", end: " << end;
    }



    return 0;
}