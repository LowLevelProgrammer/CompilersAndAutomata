#include "automata/dfa/dfa.h"
#include "doctest/doctest.h"

TEST_CASE("Valid DFA passes validation") {
  DFA dfa;

  dfa.AddState("q0");
  dfa.AddState("q1");

  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q1");

  dfa.AddTransition("q0", '0', "q0");
  dfa.AddTransition("q0", '1', "q1");

  dfa.AddTransition("q1", '0', "q0");
  dfa.AddTransition("q1", '1', "q1");

  CHECK(dfa.Validate() == true);
}

TEST_CASE("DFA with missing start state fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with invalid start state fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');

  dfa.SetStartState("q1");

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with invalid accepting state fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q1");

  dfa.AddTransition("q0", '0', "q0");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with invalid transition destination fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q1");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with extra transition source state fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");

  dfa.AddTransition("q1", '0', "q0");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with missing transition symbol fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');
  dfa.AddSymbol('1');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with invalid transition symbol fails validation") {
  DFA dfa;

  dfa.AddState("q0");

  dfa.AddSymbol('0');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q0");

  dfa.AddTransition("q0", '0', "q0");
  dfa.AddTransition("q0", '1', "q0");

  CHECK(dfa.Validate() == false);
}

TEST_CASE("DFA with missing transition source state fails validation") {
  DFA dfa;

  dfa.AddState("q0");
  dfa.AddState("q1");

  dfa.AddSymbol('0');

  dfa.SetStartState("q0");

  dfa.AddAcceptState("q1");

  dfa.AddTransition("q0", '0', "q1");

  CHECK(dfa.Validate() == false);
}
