#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

class NFA {
public:
  NFA();
  ~NFA();

  void AddSymbol(char alphabet);
  void AddState(const std::string &state);
  void SetStartState(const std::string &state);
  void AddAcceptState(const std::string &state);
  void AddTransition(const std::string &currentState, const char &symbol,
                     const std::unordered_set<std::string> &nextStates);
  bool Accepts(const std::string &input) const;
  void Print() const;

  bool Validate() const;

private:
  // NFA (Q, Σ, q0, F, δ)

  std::unordered_set<std::string> m_States;
  std::unordered_set<char> m_Alphabet;

  std::string m_StartState;
  std::unordered_set<std::string> m_AcceptingStates;

  // transition[current_state][input_symbol] = next_states
  std::unordered_map<std::string,
                     std::unordered_map<char, std::unordered_set<std::string>>>
      m_Transitions;

private:
  bool AcceptsRecursion(const std::string &str, std::string currentState) const;
};
