#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
class DFA {
public:
  DFA();
  ~DFA();

  void AddSymbol(char alphabet);
  void AddState(const std::string &state);
  void SetStartState(const std::string &state);
  void AddAcceptState(const std::string &state);
  void AddTransition(const std::string &currentState, const char &symbol,
                     const std::string &nextState);
  bool Accepts(const std::string &input) const;
  void Print() const;

  bool Validate() const;

private:
  // DFA = (Q, Σ, δ, q0, F)

  std::unordered_set<std::string> m_States;
  std::unordered_set<char> m_Alphabet;

  // transition[current_state][sybmol] = next_state
  std::unordered_map<std::string, std::unordered_map<char, std::string>>
      m_Transitions;

  std::string m_StartState;
  std::unordered_set<std::string> m_AcceptingStates;

  mutable bool m_IsValidated = false;

  std::unordered_set<std::string> m_DeadStates;
  mutable bool m_DeadStatesComputed = false;

private:
  void InferDeadStates();
};
