#include <iostream>
#include "student_info.h"


StudentInformation::StudentInformation(std::string name, std::string id) : m_name(name), m_id(id){
}

StudentInformation::~StudentInformation(){
}

void StudentInformation::print_info(){
    std::cout << "name: " << m_name << ", ID: " << m_id << std::endl;
}

void StudentInformation::print_separator(){
    const int COUNT = 10;
    for (int i=0; i < 10; i++){
        std::cout << "-";
    }
}