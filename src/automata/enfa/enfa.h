#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

static constexpr char EPSILON = '\0';

class ENFA {
public:
  ENFA();
  ~ENFA();

  void AddSymbol(char alphabet);
  void AddState(const std::string &state);
  void SetStartState(const std::string &state);
  void AddAcceptState(const std::string &state);
  void AddTransition(const std::string &currentState, const char &symbol,
                     const std::unordered_set<std::string> &nextStates);
  bool Accepts(const std::string &input) const;
  void Print() const;

  bool Prepare();

private:
  // eNFA (Q, Σ, q0, F, δ)
  std::unordered_set<std::string> m_States;
  std::unordered_set<char> m_Alphabet;
  std::string m_StartState;

  std::unordered_set<std::string> m_AcceptingStates;

  // δ: Q x (Σ u {𝜀}) -> 2^Q
  std::unordered_map<std::string,
                     std::unordered_map<char, std::unordered_set<std::string>>>
      m_Transitions;

private:
  bool Validate() const;
};
