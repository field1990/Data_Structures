#include <iostream>
#include "student_info.h"

using namespace std;


int main(){

    StudentInformation student_one("John", "12345");
    student_one.print_info();
    student_one.print_separator();

    return 0;

}