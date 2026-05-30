#include "enfa.h"
#include <iostream>

int main(int argc, char *argv[]) {
  // eNFA for zero or more a's followed by zero or more b's
  // i.e. (a* b*)
  ENFA enfa;

  enfa.AddState("q0");
  enfa.AddState("q1");
  enfa.AddState("q2");

  enfa.AddSymbol('a');
  enfa.AddSymbol('b');

  enfa.SetStartState("q0");
  enfa.AddAcceptState("q2");

  enfa.AddTransition("q0", 'a', {"q0"});
  enfa.AddTransition("q0", EPSILON, {"q1"});

  enfa.AddTransition("q1", 'b', {"q1"});
  enfa.AddTransition("q1", EPSILON, {"q2"});

  if (!enfa.Prepare()) {
    std::cerr << "eNFA is not valid" << std::endl;
    exit(EXIT_FAILURE);
  }

  enfa.Print();
}
