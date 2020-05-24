#ifndef AUTOMATES_IFSM_H
#define AUTOMATES_IFSM_H

#include <set>
#include <iostream>


template<typename ContainerType, typename Return_t = int>
class IFSM
{
public:
	using Iter = typename ContainerType::const_iterator;
	using State_t = int32_t;
	using FinalStatesSet = std::set<State_t>;

	// constructors
	explicit IFSM(State_t initialState)
			: m_currState(initialState), m_initialState(initialState), m_finalStates(nullptr)
	{ }
	// destructors
	virtual ~IFSM() {
		delete m_finalStates;
	}

		virtual Return_t process(const Iter beg, const Iter end) {
		for (Iter it = beg; it != end; ++it) {
			Return_t r = m_process(it);
			if (m_returnCondition(r))
				return r;  // Return value of specified type
		}
		return m_processEndDefaultReturn();
	}

	virtual Return_t process(const ContainerType& cont) {
		return process(cont.begin(), cont.end());
	}

	virtual void setFinalStates(FinalStatesSet&& states) {
		m_finalStates = new FinalStatesSet(std::move(states));
	}

	virtual void resetFSM() {
		m_currState = m_initialState;
	}

protected:
	virtual Return_t m_process(Iter& iter) = 0;

	[[nodiscard]] virtual bool m_returnCondition(const Return_t v) const {
		return m_finalStates->find(m_currState) != m_finalStates->end();  // If final state reached or error occurred
	}

	[[nodiscard]] virtual Return_t m_processEndDefaultReturn() const {
//		std::cout << "Process ended without return condition" << std::endl;
		return m_currState;
	};

	State_t m_currState;
	State_t m_initialState;
	FinalStatesSet* m_finalStates;
};


#endif //AUTOMATES_IFSM_H
