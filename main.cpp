#include <iostream>
#include <string>

#include "MainFSM.h"


// do while i < 10 i = 5 + a loop
// do while 5 > 10 i = 5 + a loop
// do i = i + 1 until i = 10 loop
// do while i < 9.1 loop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	MainFSM fsm;
	//fsm.setFinalStates({-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, 11});

//	while (true) {
		fsm.resetFSM();

		std::string str;
		while (getline(std::cin, str), !str.empty())
			fsm.process(str.begin(), str.end());

		fsm.printResult();
//	}
	return 0;
}
#pragma clang diagnostic pop
