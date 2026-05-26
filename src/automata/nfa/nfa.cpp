#include "nfa.h"

#include <algorithm>
#include <format>
#include <print>
#include <string>
#include <unordered_set>
#include <vector>

NFA::NFA() {}

NFA::~NFA() {}

void NFA::AddSymbol(char alphabet) { m_Alphabet.insert(alphabet); }

void NFA::AddState(const std::string &state) { m_States.insert(state); }

void NFA::SetStartState(const std::string &state) { m_StartState = state; }

void NFA::AddAcceptState(const std::string &state) {
  m_AcceptingStates.insert(state);
}

void NFA::AddTransition(const std::string &currentState, const char &symbol,
                        const std::unordered_set<std::string> &nextStates) {
  m_Transitions[currentState][symbol] = nextStates;
}

bool NFA::Accepts(const std::string &input) const {
  return AcceptsRecursion(input, m_StartState);
}

bool NFA::AcceptsRecursion(const std::string &str,
                           std::string currentState) const {
  if (str.empty()) {
    if (m_AcceptingStates.contains(currentState))
      return true;
    else
      return false;
  }
  std::unordered_set<std::string> nextStates =
      m_Transitions.at(currentState).at(str[0]);

  if (nextStates.size() == 1 && nextStates.contains("$")) {
    return false;
  }

  bool anyAccepts = false;
  for (const auto &nextState : nextStates) {
    bool result = AcceptsRecursion(str.substr(1), nextState);

    if (result)
      anyAccepts = true;
  }

  return anyAccepts;
}

void NFA::Print() const {

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

  std::vector<std::string> transitions;

  for (const auto &[source, transition] : m_Transitions) {
    for (const auto &[symbol, nextStates] : transition) {
      std::vector<std::string> nextStatesSet;

      for (const auto &nextState : nextStates) {
        nextStatesSet.push_back(nextState);
      }
      std::sort(nextStatesSet.begin(), nextStatesSet.end());

      transitions.push_back(
          std::format("({}, {}) -> {}", source, symbol, nextStatesSet));
    }
  }

  std::sort(transitions.begin(), transitions.end());

  std::println("Transition function: ");
  for (const auto &transition : transitions) {
    std::println("{}", transition);
  }
}

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
        if (nextState == "$")
          continue;
        else if (m_States.find(nextState) == m_States.end()) {
          return false;
        }
      }
    }
  }

  return true;
}
