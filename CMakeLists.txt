cmake_minimum_required(VERSION 3.16)
project(automates)

set(CMAKE_CXX_STANDARD 17)

add_executable(automates main.cpp IFSM.h VariableFSM.h MainFSM.h IntegerFSM.h)