#ifndef AUTOMATES_INTEGERFSM_H
#define AUTOMATES_INTEGERFSM_H

#include "IFSM.h"

class IntegerFSM : public IFSM<std::string>
{
public:
	IntegerFSM() : IFSM(0), _counter(0) {
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
			if (_isDigitSymbol(*iter))
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
	static bool _isDigitSymbol(char c) {
		return (c >= '0' && c <= '9');
	}

	int _counter;
};


#endif //AUTOMATES_INTEGERFSM_H
