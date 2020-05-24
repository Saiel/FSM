#ifndef AUTOMATES_VARIABLEFSM_H
#define AUTOMATES_VARIABLEFSM_H

#include "IFSM.h"

class VariableFSM : public IFSM<std::string>
{
public:
	VariableFSM() : IFSM(0), _counter(0) {
		m_finalStates = new FinalStatesSet({1});
	}

	void resetFSM() override {
		IFSM::resetFSM();
		_counter = 0;
	}

protected:
	int m_process(Iter& iter) override
	{
		switch (m_currState) {
		case 0:
			if (_isNameSymbol(*iter))
				return ++_counter;
			else {
				m_currState = 1;
				return _counter;
			}
		case 1:
			return _counter;
		}
	}

	[[nodiscard]] int m_processEndDefaultReturn() const override {
		return _counter;
	}

private:
	static bool _isNameSymbol(char c) {
		return (c >= 'a' && c <= 'z' ||
		        c >= 'A' && c <= 'Z' ||
		        c >= '0' && c <= '9');
	}

	int _counter;
};


#endif //AUTOMATES_VARIABLEFSM_H
