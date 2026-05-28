#include "automata/nfa/nfa.h"
#include "doctest/doctest.h"

TEST_CASE("Valid NFA prepares successfully") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q0");

  nfa.AddTransition("q0", 'a', {"q0"});

  CHECK(nfa.Prepare() == true);
}

TEST_CASE("NFA with missing start state fails prepare") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.AddAcceptState("q0");

  nfa.AddTransition("q0", 'a', {"q0"});

  CHECK(nfa.Prepare() == false);
}

TEST_CASE("NFA with invalid start state fails prepare") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.SetStartState("q1");

  nfa.AddTransition("q0", 'a', {"q0"});

  CHECK(nfa.Prepare() == false);
}

TEST_CASE("NFA with invalid accepting state fails prepare") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q1");

  nfa.AddTransition("q0", 'a', {"q0"});

  CHECK(nfa.Prepare() == false);
}

TEST_CASE("NFA with invalid transition source state fails prepare") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");

  nfa.AddTransition("q1", 'a', {"q0"});

  CHECK(nfa.Prepare() == false);
}

TEST_CASE("NFA with invalid transition symbol fails prepare") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");

  nfa.AddTransition("q0", 'b', {"q0"});

  CHECK(nfa.Prepare() == false);
}

TEST_CASE("NFA with invalid destination state fails prepare") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");

  nfa.AddTransition("q0", 'a', {"q1"});

  CHECK(nfa.Prepare() == false);
}

TEST_CASE("NFA allows sparse transition tables") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('a');
  nfa.AddSymbol('b');

  nfa.SetStartState("q0");

  nfa.AddTransition("q0", 'a', {"q0"});

  CHECK(nfa.Prepare() == true);
}

TEST_CASE("NFA allows states with no outgoing transitions") {
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q1");

  nfa.AddTransition("q0", 'a', {"q1"});

  CHECK(nfa.Prepare() == true);
}
