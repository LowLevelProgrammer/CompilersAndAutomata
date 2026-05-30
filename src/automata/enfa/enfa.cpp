#include "enfa.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <print>
#include <vector>

ENFA ::ENFA() {}

ENFA ::~ENFA() {}

void ENFA::AddSymbol(char alphabet) {
  if (alphabet == EPSILON) {
    std::cerr << "ENFA::AddSymbol(): epsilon cannot be added to the alphabet"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  m_Alphabet.insert(alphabet);
}

void ENFA::AddState(const std::string &state) { m_States.insert(state); }

void ENFA::SetStartState(const std::string &state) { m_StartState = state; }

void ENFA::AddAcceptState(const std::string &state) {
  m_AcceptingStates.insert(state);
}

void ENFA::AddTransition(const std::string &currentState, const char &symbol,
                         const std::unordered_set<std::string> &nextStates) {
  m_Transitions[currentState][symbol] = nextStates;
}

bool ENFA::Accepts(const std::string &input) const {}

void ENFA::Print() const {

  std::vector<std::string> states;
  for (const auto &state : m_States) {
    states.push_back(state);
  }
  std::sort(states.begin(), states.end());
  std::println("Set of all states: {}", states);

  std::vector<char> alphabet;
  for (const auto &symbol : m_Alphabet) {
    alphabet.push_back(symbol);
  }
  std::sort(alphabet.begin(), alphabet.end());
  std::println("Set of alphabet: {}", alphabet);

  std::println("Start state: {}", m_StartState);

  std::vector<std::string> acceptingStates;
  for (const auto &acceptState : m_AcceptingStates) {
    acceptingStates.push_back(acceptState);
  }

  std::sort(acceptingStates.begin(), acceptingStates.end());
  std::println("Set of accepting states: {}", acceptingStates);

  std::vector<std::string> transitionsString;

  for (const auto &[source, transitions] : m_Transitions) {
    for (const auto &[symbol, nextStates] : transitions) {
      std::vector<std::string> nextStatesSet;

      for (const auto &nextState : nextStates) {
        nextStatesSet.push_back(nextState);
      }
      std::sort(nextStatesSet.begin(), nextStatesSet.end());

      if (symbol == EPSILON) {
        transitionsString.push_back(
            std::format("({}, \"\") -> {}", source, nextStatesSet));
      } else {
        transitionsString.push_back(
            std::format("({}, {}) -> {}", source, symbol, nextStatesSet));
      }
    }
  }

  std::sort(transitionsString.begin(), transitionsString.end());

  std::println("Transition function: ");
  for (const auto &transition : transitionsString) {
    std::println("{}", transition);
  }
}

bool ENFA::Prepare() {
  if (!Validate()) {
    return false;
  }

  return true;
}

bool ENFA::Validate() const {
  // Validations:
  // 1. Start state exists
  // 2. Start state belongs to set of all states
  // 3. Accepting states is subset of set of all states
  // 4. All current states in transition function are valid states
  // 5. Transitions on current states only exists for alphabet union epsilon
  // 6. Transition goes to a valid next state

  if (m_StartState.empty())
    return false;

  if (!m_States.contains(m_StartState)) {
    return false;
  }

  for (const auto &acceptingState : m_AcceptingStates) {
    if (!m_States.contains(acceptingState)) {
      return false;
    }
  }

  for (const auto &[current, transitions] : m_Transitions) {
    if (!m_States.contains(current)) {
      return false;
    }

    for (const auto &[symbol, nextStates] : transitions) {
      if (!(m_Alphabet.contains(symbol) || symbol == EPSILON)) {
        return false;
      }

      for (const auto &nextState : nextStates) {
        if (!m_States.contains(nextState)) {
          return false;
        }
      }
    }
  }

  return true;
}
