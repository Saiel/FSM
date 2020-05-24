#ifndef AUTOMATES_MAINFSM_H
#define AUTOMATES_MAINFSM_H

#include "VariableFSM.h"
#include "IntegerFSM.h"

class MainFSM : public IFSM<std::string>
{
public:
	MainFSM()
		: IFSM(0), _varFSM(new VariableFSM), _intFSM(new IntegerFSM)
	{
		MainFSM::setFinalStates({-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, 11});
	}

	void printResult() {
		switch (m_currState) {
		case 0: {
			std::cout << "Statement is not complete." << std::endl;
			break;
		}
		case -1: {
			std::cout << "Expected first word 'do'." << std::endl;
			break;
		}
		case -2: {
			std::cout << "Expected first word 'while'." << std::endl;
			break;
		}
		case -3: {
			std::cout << "Error on cycle condition. Expected variable, beginning with latin letter." << std::endl;
			break;
		}
		case -4: {
			std::cout << "Error on cycle condition. Expected '<' or '>'." << std::endl;
			break;
		}
		case -5: {
			std::cout << "Error on cycle condition. Expected integer." << std::endl;
			break;
		}
		case -6:
		case -7: {
			std::cout << "Error in cycle body. Expected variable assignment." << std::endl;
			break;
		}
		case -8:
		case -9:
		case -10: {
			std::cout << "Error in variable assignment. Expected one arithmetic operation "
			             "with variables or/and integers." << std::endl;
			break;
		}
		case -11: {
			std::cout << "Error in cycle end. Expected 'loop'." << std::endl;
			break;
		}
		case 11: {
			std::cout << "OK." << std::endl;
			break;
		}
		}
	}

protected:
	int m_process(Iter& iter) override
	{
		if (_isSkippable(*iter)) return m_currState;

		switch (m_currState) {
			case 0:
				return _expect(iter, "do", 1);
			case 1:
				return _expect(iter, "while", 2);
			case 2: {
				return _processValue(iter, {{'a', 'z'}, {'A', 'Z'}}, 3, _varFSM);
			}
			case 3:
				return _expect(iter, {'<', '>'}, 4);
			case 4:
				return _processValue(iter, {{'0', '9'}}, 5, _intFSM);
			case 5:
				return _processValue(iter, {{'a', 'z'}, {'A', 'Z'}}, 6, _varFSM);
			case 6:
				return _expect(iter, '=', 7);
			case 7: {
				int state = _processValue(iter, {{'a', 'z'}, {'A', 'Z'}}, 8, _varFSM);
				if (state < 0)
					state = _processValue(iter, {{'0', '9'}}, 8, _intFSM);
				return state;
			}
			case 8:
				return _expect(iter, {'+', '-', '/', '*'}, 9);
			case 9: {
				int state = _processValue(iter, {{'a', 'z'}, {'A', 'Z'}}, 10, _varFSM);
				if (state < 0)
					state = _processValue(iter, {{'0', '9'}}, 10, _intFSM);
				return state;
			}
			case 10:
				return _expect(iter, "loop", 11);
		}

		return 0;
	}

private:
	int _expect(Iter& iter, const std::string& expectedStr, const State_t nextState) {
		if (_isPointToSubstr(iter, expectedStr)) {
			m_currState = nextState;
			iter += expectedStr.size() - 1;
		} else {
			m_currState = -nextState;
		}
		return m_currState;
	}

	int _expect(const Iter iter, const std::initializer_list<std::pair<char, char>> ranges, const State_t nextState) {
		bool isInRange = false;
		for (auto range: ranges) {
			if (range.first > range.second)
				continue;
			if (*iter >= range.first && *iter <= range.second) {
				isInRange = true;
				break;
			}
		}
		if (isInRange)
			m_currState = nextState;
		else
			m_currState = - nextState;
		return m_currState;
	}

	int _expect(const Iter iter, const std::initializer_list<char> expectedChars, const State_t nextState) {
		bool isInRange = false;
		for (char it: expectedChars)
			if (*iter == it) {
				isInRange = true;
				break;
			}

		if (isInRange)
			m_currState = nextState;
		else
			m_currState = -nextState;
		return m_currState;
	}

	int _expect(const Iter iter, const char expectedChars, const State_t nextState) {
		return _expect(iter, {expectedChars}, nextState);
	}

	int _processValue(
			Iter& iter,
			const std::initializer_list<std::pair<char, char>> beginCharRanges,
			const State_t nextState,
			IFSM* const fsm
	) {
		int state = _expect(iter, beginCharRanges, nextState);
		if (state > 0) {
			fsm->resetFSM();
			std::string temp(&*iter);
			int size = fsm->process(temp);
			iter += size - 1;

		}
		return state;
	}

	static bool _isPointToSubstr(Iter iter, const std::string& refStr) {
		int i = 0;
		for (auto it : refStr) {
			if (it != *(iter + i))
				return false;
			++i;
		}
		return true;
	}

	static bool _isSkippable(const char c) {
		return c == ' '
			|| c == '\n'
			|| c == '\0'
			|| c == '\t';
	}

	VariableFSM* _varFSM;
	IntegerFSM*  _intFSM;
};


#endif //AUTOMATES_MAINFSM_H
