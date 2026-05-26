#include <iostream>
#include <print>
#include <string>
#include <unordered_set>

#include "nfa.h"

int main(int argc, char *argv[]) {
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");
  nfa.AddState("q2");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q2");

  std::unordered_set<std::string> q00;
  q00.insert("$");
  nfa.AddTransition("q0", '0', q00);

  std::unordered_set<std::string> q01;
  q01.insert("q0");
  q01.insert("q1");
  nfa.AddTransition("q0", '1', q01);

  std::unordered_set<std::string> q10;
  q10.insert("q1");
  q10.insert("q2");
  nfa.AddTransition("q1", '0', q10);

  std::unordered_set<std::string> q11;
  q11.insert("$");
  nfa.AddTransition("q1", '1', q11);

  std::unordered_set<std::string> q20;
  q20.insert("q2");
  nfa.AddTransition("q2", '0', q20);

  std::unordered_set<std::string> q21;
  q21.insert("$");
  nfa.AddTransition("q2", '1', q21);

  std::cout << "Valid: " << (nfa.Validate() ? "Yes" : "No") << std::endl;

  nfa.Print();

  std::string inputString = "110";
  std::println("Input string: {}", inputString);

  bool result = nfa.Accepts(inputString);

  std::println("String accepted by the automata: {}", result);
}
