#include <iostream>
#include <string>

#include "MainFSM.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	MainFSM fsm;
	fsm.setFinalStates({-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, 11});

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
