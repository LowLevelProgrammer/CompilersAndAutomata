#include "dfa.h"
#include <iostream>

int main(int argc, char *argv[]) {

  DFA dfa;

  dfa.AddState("q0");
  dfa.AddState("q1");
  dfa.AddState("q2");

  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q2");

  dfa.AddTransition("q0", '0', "q1");
  dfa.AddTransition("q0", '1', "q0");

  dfa.AddTransition("q1", '0', "q1");
  dfa.AddTransition("q1", '1', "q2");

  dfa.AddTransition("q2", '0', "q1");
  dfa.AddTransition("q2", '1', "q0");

  std::cout << (dfa.Accepts("111") ? "True" : "False") << std::endl;
  std::cout << (dfa.Accepts("01101") ? "True" : "False");
}
