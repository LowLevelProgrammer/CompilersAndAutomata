#include "automata/dfa/dfa.h"
#include "doctest/doctest.h"

TEST_CASE("DFA accepts binary strings ending in 01") {
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

  CHECK(dfa.Accepts("01") == true);
  CHECK(dfa.Accepts("001") == true);
  CHECK(dfa.Accepts("101") == true);
  CHECK(dfa.Accepts("11101001") == true);
  CHECK(dfa.Accepts("00001") == true);
  CHECK(dfa.Accepts("1101") == true);

  CHECK(dfa.Accepts("") == false);
  CHECK(dfa.Accepts("0") == false);
  CHECK(dfa.Accepts("1") == false);
  CHECK(dfa.Accepts("10") == false);
  CHECK(dfa.Accepts("111") == false);
  CHECK(dfa.Accepts("011") == false);
  CHECK(dfa.Accepts("111111") == false);
  CHECK(dfa.Accepts("1000") == false);
}

TEST_CASE("DFA accepting all binary strings") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.SetStartState("q0");
  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");
  dfa.AddTransition("q0", '1', "q0");

  CHECK(dfa.Accepts("") == true);
  CHECK(dfa.Accepts("0") == true);
  CHECK(dfa.Accepts("1") == true);
  CHECK(dfa.Accepts("101010") == true);
  CHECK(dfa.Accepts("111111111") == true);
}

TEST_CASE("DFA rejecting all binary strings") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.SetStartState("q0");

  dfa.AddTransition("q0", '0', "q0");
  dfa.AddTransition("q0", '1', "q0");

  CHECK(dfa.Accepts("") == false);
  CHECK(dfa.Accepts("0") == false);
  CHECK(dfa.Accepts("1") == false);
  CHECK(dfa.Accepts("101010") == false);
}
