#include "nfa.h"

NFA::NFA() {}

NFA::~NFA() {}

void NFA::AddSymbol(char alphabet) { m_Alphabet.insert(alphabet); }

void NFA::AddState(const std::string &state) { m_States.insert(state); }

void NFA::SetStartState(const std::string &state) { m_StartState = state; }

void NFA::AddAcceptState(const std::string &state) {
  m_AcceptingStates.insert(state);
}

void NFA::AddTransition(const std::string &currentState, const char &symbol,
                        const std::unordered_set<std::string> nextStates) {
  m_Transitions[currentState][symbol] = nextStates;
}

bool NFA::Accepts(const std::string &input) const {
  std::string currentState = m_StartState;
}

void NFA::Print() const {}

bool NFA::Validate() const {
  // Validations
  // 1. State state exists
  // 2. Start state belongs to set of all states
  // 3. Accepting states is subset of set of all states
  // 4. All current states in transition function are valid states
  // 5. No transition on an invalid symbol
  // 6. Transition goes to a valid next state

  if (m_StartState.empty())
    return false;

  if (m_States.find(m_StartState) == m_States.end()) {
    return false;
  }

  for (const auto &acceptingState : m_AcceptingStates) {
    if (m_States.find(acceptingState) == m_States.end()) {
      return false;
    }
  }

  for (const auto &[currentState, transition] : m_Transitions) {
    if (m_States.find(currentState) == m_States.end())
      return false;

    for (const auto &[symbol, nextStates] : transition) {
      if (m_Alphabet.find(symbol) == m_Alphabet.end()) {
        return false;
      }

      for (const auto &nextState : nextStates) {
        if (m_States.find(nextState) == m_States.end()) {
          return false;
        }
      }
    }
  }

  return true;
}
