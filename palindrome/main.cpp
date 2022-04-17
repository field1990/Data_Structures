#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

//void someFunction(string someString) {
//
//    cout << someString.substr(0) << "\n";
//
//    if (someString.substr(0) == someString.substr(someString.length() - 1)){
//
//        int n = someString.length();
//
//        for (int i = 0; i < n / 2; i++)
//            swap(someString[i], someString[n - i - 1]);
//        //https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
//
//        cout << someString << "\n";
//        cout << someString << "is a palendrome!" << "\n";
//
//    } else {
//        cout << someString.substr(0, someString.length()) << "\n";
//
//    }
//}

bool is_palindrome_recursive(char* input, int len){

    //racecar -> compare the 'r' and the rest

    if (len <= 1) return true;

    char first = input[0];
    char last = input[len - 1];

    if (first == last){
        //check the rest if it is a palindrome
        char *substr = new char[len - 1];
        strncpy(substr, &input[1], len - 2);
        substr[len - 2] = '\0';

        bool retval = is_palindrome_recursive(substr, len - 2);

        delete [] substr;
        return retval;
    }
    return false;
}

int main() {

//    string someString = "triscuit";
//    string someString2 = "cracker";
//
//    string someString3 = "monkey";
//    string someString4 = "level";
//
//
//    someFunction(someString);
//    someFunction(someString2);
//
//    someFunction(someString3);
//    someFunction(someString4);

    constexpr int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    cout << "Enter a word: ";
    cin.getline(buffer, BUFFER_SIZE);
//    if (is_palindrome(buffer, strlen(buffer))) {
//        cout << buffer << " IS a palindrome!" << endl;
//    } else {
//        cout << buffer << " IS NOT a palindrome!" << endl;
//    }
    if (is_palindrome_recursive(buffer, strlen(buffer))) {
        cout << buffer << " IS a palindrome!" << endl;
    } else {
        cout << buffer << " IS NOT a palindrome!" << endl;
    }
    return 0;
}

//#include <cstring>
//#include <iostream>
//using namespace std;
//bool is_palindrome(char* input, int len) {
//    for (int i = 0; i < len / 2; ++i) {
//        if (input[i] != input[len - i - 1]) {
//            return false;
//        }
//    }
//    return true;
//}
//bool is_palindrome_recursive(char* input, int len) {
//    // racecar -> compare the 'r' and the rest
//    if (len <= 1)
//        return true;
//    char first = input[0];
//    char last = input[len - 1];
//    if (first == last) {
//        // check the rest if it is a palindrome
//        char* substr = new char[len - 1];
//        strncpy(substr, &input[1], len - 2);
//        substr[len - 2] = '\0';
//        bool retval = is_palindrome_recursive(substr, len - 2);
//        delete[] substr;
//        return retval;
//    }
//    return false;
//}
//int main() {
//    constexpr int BUFFER_SIZE = 256;
//    char buffer[BUFFER_SIZE];
//    cout << "Enter a word: ";
//    cin.getline(buffer, BUFFER_SIZE);
//    if (is_palindrome(buffer, strlen(buffer))) {
//        cout << buffer << " IS a palindrome!" << endl;
//    } else {
//        cout << buffer << " IS NOT a palindrome!" << endl;
//    }
//    if (is_palindrome_recursive(buffer, strlen(buffer))) {
//        cout << buffer << " IS a palindrome!" << endl;
//    } else {
//        cout << buffer << " IS NOT a palindrome!" << endl;
//    }
//    return 0;
//}