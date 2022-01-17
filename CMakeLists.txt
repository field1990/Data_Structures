cmake_minimum_required(VERSION 3.20)
project(Data_Structures)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(echo echo/main.cpp)
add_executable(commandline commandline/main.cpp)
add_executable(best_practices best_practices/main.cpp
        best_practices/student_info.cpp)
add_executable(stringstream stringstream/main.cpp)