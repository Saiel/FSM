cmake_minimum_required(VERSION 3.10)
project(FSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(FSM main.cpp IFSM.h VariableFSM.h MainFSM.h IntegerFSM.h)
