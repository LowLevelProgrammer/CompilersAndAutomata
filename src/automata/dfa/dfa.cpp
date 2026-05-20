#include "dfa.h"

#include "assert.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

DFA::DFA() {}

DFA::~DFA() {}

void DFA::AddSymbol(char alphabet) { m_Alphabet.insert(alphabet); }

void DFA::AddState(const std::string &state) { m_States.insert(state); }

void DFA::SetStartState(const std::string &state) { m_StartState = state; }

void DFA::AddAcceptState(const std::string &state) {
  m_AcceptingStates.insert(state);
}

void DFA::AddTransition(const std::string &currentState, const char &symbol,
                        const std::string &nextState) {
  m_Transitions[currentState][symbol] = nextState;
}

void DFA::Print() const {
  std::vector<std::string> states;
  std::cout << "Set of all states: { ";
  for (const auto &state : m_States) {
    states.push_back(state);
  }
  std::sort(states.begin(), states.end());
  for (const auto &state : states) {
    std::cout << state << " ";
  }
  std::cout << "}\n";

  std::vector<char> alphabet;
  std::cout << "Set of all input symbols: { ";
  for (const auto &symbol : m_Alphabet) {
    alphabet.push_back(symbol);
  }
  std::sort(alphabet.begin(), alphabet.end());
  for (const auto &symbol : alphabet) {
    std::cout << symbol << " ";
  }
  std::cout << "}\n";

  std::cout << "Start state: " << m_StartState << std::endl;

  std::vector<std::string> acceptingStates;
  std::cout << "Set of accepting states: { ";
  for (const auto &acceptState : m_AcceptingStates) {
    acceptingStates.push_back(acceptState);
  }

  std::sort(acceptingStates.begin(), acceptingStates.end());
  for (const auto &acceptState : acceptingStates) {
    std::cout << acceptState << " ";
  }
  std::cout << "}\n";

  std::cout << "Transition function: \n";
  std::vector<std::string> transitions;
  for (const auto &[source, transition] : m_Transitions) {
    for (const auto &[symbol, destination] : transition) {
      transitions.push_back(
          std::format("({}, {}) -> {}", source, symbol, destination));
    }
  }

  // TODO implement a better way than lexicographic sort as this will fail in
  // cases such as q10 < q2 in lexicographic sort
  std::sort(transitions.begin(), transitions.end());

  for (const auto &transition : transitions) {
    std::cout << transition << std::endl;
  }
}

bool DFA::Accepts(const std::string &input) const {
  if (!m_IsValidated) {
    Validate();
    m_IsValidated = true;
  }

  std::string currentState = m_StartState;
  for (int i = 0; i < input.size(); i++) {
    if (m_Alphabet.find(input[i]) == m_Alphabet.end()) {
      return false;
    } else if (m_DeadStates.find(currentState) != m_DeadStates.end()) {
      // if current state reached a dead state then string is not accepted
      return false;
    } else {
      currentState = m_Transitions.at(currentState).at(input[i]);
    }
  }

  if (m_AcceptingStates.find(currentState) != m_AcceptingStates.end())
    return true;
  else
    return false;
}

bool DFA::Validate() const {
  // Need to check:
  // 1. Check there's a start state
  // 2. Start state is valid
  // 3. All accepting states are valid
  // 4. All states exists in the source state of transition map
  // 5. No invalid state in the source state transition map exists
  // 6. All states have transitions for all the input symbols
  // 7. No invalid input symbol in the transition map exists
  // 8. The transitions goes to a valid state

  // Check start state exists
  if (m_StartState.empty()) {
    return false;
  }

  // Check start state valid
  if (m_States.find(m_StartState) == m_States.end())
    return false;

  // Check accepting states are valid
  for (const auto &acceptState : m_AcceptingStates) {
    if (m_States.find(acceptState) == m_States.end()) {
      return false;
    }
  }

  // Check if all and only valid states exists in source state of transition map
  std::unordered_set<std::string> transitionSourceStates;

  for (const auto &[sourceState, _] : m_Transitions) {
    transitionSourceStates.insert(sourceState);
  }

  if (transitionSourceStates != m_States)
    return false;

  // Check if transitions for all defined and only defined input symbols exist
  for (const auto &[_, transition] : m_Transitions) {
    std::unordered_set<char> allTransitionSymbols;

    for (const auto &[symbol, destination] : transition) {
      allTransitionSymbols.insert(symbol);
    }

    if (allTransitionSymbols != m_Alphabet) {
      return false;
    }
  }

  // Check if destination state in transition function is a valid state
  for (const auto &[_, transition] : m_Transitions) {
    for (const auto &[_, destination] : transition) {
      if (m_States.find(destination) == m_States.end())
        return false;
    }
  }

  return true;
}

// TODO implement
void DFA::InferDeadStates() {}
