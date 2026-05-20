#include "automata/dfa/dfa.h"
#include "doctest/doctest.h"

TEST_CASE("DFA rejects strings containing symbols outside alphabet") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");
  dfa.AddTransition("q0", '1', "q0");

  CHECK(dfa.Accepts("2") == false);
  CHECK(dfa.Accepts("012") == false);
  CHECK(dfa.Accepts("abc") == false);
  CHECK(dfa.Accepts("10a01") == false);
  CHECK(dfa.Accepts("999") == false);
}

TEST_CASE("DFA rejects symbols not present in unary alphabet") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('1');

  dfa.SetStartState("q0");
  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '1', "q0");

  CHECK(dfa.Accepts("0") == false);
  CHECK(dfa.Accepts("10") == false);
  CHECK(dfa.Accepts("101") == false);
}
