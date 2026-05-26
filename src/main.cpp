#include <print>
#include <string>

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

  nfa.AddTransition("q0", '0', {});
  nfa.AddTransition("q0", '1', {"q0", "q1"});

  nfa.AddTransition("q1", '0', {"q1", "q2"});
  nfa.AddTransition("q1", '1', {});

  nfa.AddTransition("q2", '0', {"q2"});
  nfa.AddTransition("q2", '1', {});

  if (!nfa.Validate()) {
    exit(EXIT_FAILURE);
  }

  nfa.Print();

  std::string inputString = "0";
  std::println("Input string: {}", inputString);
  bool result = nfa.Accepts(inputString);
  std::println("String accepted by the automata: {}", result);

  std::string inputString2 = "1";
  std::println("Input string: {}", inputString2);
  bool result2 = nfa.Accepts(inputString2);
  std::println("String accepted by the automata: {}", result2);

  std::string inputString3 = "01";
  std::println("Input string: {}", inputString3);
  bool result3 = nfa.Accepts(inputString3);
  std::println("String accepted by the automata: {}", result3);

  std::string inputString4 = "10";
  std::println("Input string: {}", inputString4);
  std::println("String accepted by the automata: {}",
               nfa.Accepts(inputString4));

  std::string inputString5 = "1110000";
  std::println("Input string: {}", inputString5);
  std::println("String accepted by the automata: {}",
               nfa.Accepts(inputString5));

  std::string inputString6 = "11010000";
  std::println("Input string: {}", inputString6);
  std::println("String accepted by the automata: {}",
               nfa.Accepts(inputString6));
}
