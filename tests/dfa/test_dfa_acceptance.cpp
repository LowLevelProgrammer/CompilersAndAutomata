#include "automata/dfa/dfa.h"
#include "doctest/doctest.h"

TEST_CASE("DFA accepts binary strings ending in 01") {
  DFA dfa;

  // Alphabet
  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  // States
  dfa.AddState("q0");
  dfa.AddState("q1");
  dfa.AddState("q2");

  // Start state
  dfa.SetStartState("q0");

  // Accept state
  dfa.AddAcceptState("q2");

  // Transitions
  dfa.AddTransition("q0", '0', "q1");
  dfa.AddTransition("q0", '1', "q0");

  dfa.AddTransition("q1", '0', "q1");
  dfa.AddTransition("q1", '1', "q2");

  dfa.AddTransition("q2", '0', "q1");
  dfa.AddTransition("q2", '1', "q0");

  CHECK(dfa.Accepts("00") == false);
  CHECK(dfa.Accepts("01") == true);
  CHECK(dfa.Accepts("10") == false);
  CHECK(dfa.Accepts("11") == false);

  CHECK(dfa.Accepts("101") == true);
  CHECK(dfa.Accepts("001") == true);
  CHECK(dfa.Accepts("011") == false);
  CHECK(dfa.Accepts("11101001") == true);
}
