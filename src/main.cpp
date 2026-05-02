#include <iostream>

#include "dfa.h"

int main(int argc, char *argv[]) {
  DFA dfa;

  // Example DFA for string ending in '01'
  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.AddState("q0");
  dfa.AddState("q1");
  dfa.AddState("q2");

  dfa.SetStartState("q0");
  dfa.AddAcceptState("q2");

  dfa.AddTransition("q0", '0', "q1");
  dfa.AddTransition("q0", '1', "q0");

  dfa.AddTransition("q1", '0', "q1");
  dfa.AddTransition("q1", '1', "q2");

  dfa.AddTransition("q2", '0', "q1");
  dfa.AddTransition("q2", '1', "q0");

  dfa.Print();

  std::cout << dfa.Accepts("00") << std::endl;
  std::cout << dfa.Accepts("01") << std::endl;
  std::cout << dfa.Accepts("10") << std::endl;
  std::cout << dfa.Accepts("11") << std::endl;

  std::cout << std::endl;

  std::cout << dfa.Accepts("101") << std::endl;
  std::cout << dfa.Accepts("001") << std::endl;
  std::cout << dfa.Accepts("011") << std::endl;
  std::cout << dfa.Accepts("11101001") << std::endl;

  std::cout << (dfa.Validate() ? "true" : "false");
  return 0;
}
