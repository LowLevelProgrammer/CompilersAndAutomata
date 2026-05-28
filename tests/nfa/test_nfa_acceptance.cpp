#include "automata/nfa/nfa.h"
#include "doctest/doctest.h"

TEST_CASE("NFA accepts strings matching 1+0+") {
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");
  nfa.AddState("q2");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q2");

  nfa.AddTransition("q0", '1', {"q0", "q1"});
  nfa.AddTransition("q1", '0', {"q1", "q2"});
  nfa.AddTransition("q2", '0', {"q2"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("10") == true);
  CHECK(nfa.Accepts("110") == true);
  CHECK(nfa.Accepts("111000") == true);
  CHECK(nfa.Accepts("111100000") == true);

  CHECK(nfa.Accepts("") == false);
  CHECK(nfa.Accepts("0") == false);
  CHECK(nfa.Accepts("1") == false);
  CHECK(nfa.Accepts("00") == false);
  CHECK(nfa.Accepts("01") == false);
  CHECK(nfa.Accepts("11") == false);
  CHECK(nfa.Accepts("101010") == false);
  CHECK(nfa.Accepts("111") == false);
  CHECK(nfa.Accepts("0000") == false);
}

TEST_CASE("NFA accepts all binary strings") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q0");

  nfa.AddTransition("q0", '0', {"q0"});
  nfa.AddTransition("q0", '1', {"q0"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("") == true);
  CHECK(nfa.Accepts("0") == true);
  CHECK(nfa.Accepts("1") == true);
  CHECK(nfa.Accepts("101010") == true);
  CHECK(nfa.Accepts("111111") == true);
  CHECK(nfa.Accepts("000000") == true);
}

TEST_CASE("NFA rejects all strings") {
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("") == false);
  CHECK(nfa.Accepts("0") == false);
  CHECK(nfa.Accepts("1") == false);
  CHECK(nfa.Accepts("1010") == false);
}

TEST_CASE("NFA accepts strings ending in 10") {
  // (0 + 1)* 10
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");
  nfa.AddState("q2");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q2");

  nfa.AddTransition("q0", '0', {"q0"});
  nfa.AddTransition("q0", '1', {"q0", "q1"});

  nfa.AddTransition("q1", '0', {"q2"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("10") == true);
  CHECK(nfa.Accepts("110") == true);
  CHECK(nfa.Accepts("11110") == true);
  CHECK(nfa.Accepts("01010") == true);
  CHECK(nfa.Accepts("0010") == true);

  CHECK(nfa.Accepts("") == false);
  CHECK(nfa.Accepts("01") == false);
  CHECK(nfa.Accepts("101") == false);
  CHECK(nfa.Accepts("111") == false);
}

TEST_CASE("NFA handles nondeterministic branching correctly") {
  // ab + aa
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");
  nfa.AddState("q2");
  nfa.AddState("q3");

  nfa.AddSymbol('a');
  nfa.AddSymbol('b');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q3");

  nfa.AddTransition("q0", 'a', {"q1", "q2"});
  nfa.AddTransition("q1", 'b', {"q3"});
  nfa.AddTransition("q2", 'a', {"q3"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("ab") == true);
  CHECK(nfa.Accepts("aa") == true);

  CHECK(nfa.Accepts("a") == false);
  CHECK(nfa.Accepts("b") == false);
  CHECK(nfa.Accepts("ba") == false);
  CHECK(nfa.Accepts("bb") == false);
  CHECK(nfa.Accepts("abb") == false);
  CHECK(nfa.Accepts("aab") == false);
  CHECK(nfa.Accepts("abb") == false);
  CHECK(nfa.Accepts("aba") == false);
  CHECK(nfa.Accepts("aaa") == false);
}

TEST_CASE("NFA accepts if at least one branch accepts") {
  NFA nfa;
  // aa

  nfa.AddState("q0");
  nfa.AddState("q1");
  nfa.AddState("q2");
  nfa.AddState("q3");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q3");

  nfa.AddTransition("q0", 'a', {"q1", "q2"});
  nfa.AddTransition("q2", 'a', {"q3"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("aa") == true);

  CHECK(nfa.Accepts("a") == false);
  CHECK(nfa.Accepts("aaa") == false);
  CHECK(nfa.Accepts("ab") == false);
  CHECK(nfa.Accepts("aab") == false);
}

TEST_CASE("NFA rejects strings with symbols outside alphabet") {
  // (0 + 1)*
  NFA nfa;

  nfa.AddState("q0");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q0");

  nfa.AddTransition("q0", '0', {"q0"});
  nfa.AddTransition("q0", '1', {"q0"});

  CHECK(nfa.Prepare());
  CHECK(nfa.Accepts("0") == true);
  CHECK(nfa.Accepts("1") == true);
  CHECK(nfa.Accepts("01") == true);
  CHECK(nfa.Accepts("10") == true);
  CHECK(nfa.Accepts("11") == true);
  CHECK(nfa.Accepts("101") == true);

  CHECK(nfa.Accepts("2") == false);
  CHECK(nfa.Accepts("102") == false);
  CHECK(nfa.Accepts("abc") == false);
  CHECK(nfa.Accepts("hello") == false);
}

TEST_CASE("NFA handles states with no outgoing transitions") {
  // a
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");

  nfa.AddSymbol('a');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q1");

  nfa.AddTransition("q0", 'a', {"q1"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("a") == true);

  CHECK(nfa.Accepts("") == false);
  CHECK(nfa.Accepts("aa") == false);
}

TEST_CASE("Prepare canonicalizes sparse transition table") {
  NFA nfa;

  nfa.AddState("q0");
  nfa.AddState("q1");

  nfa.AddSymbol('0');
  nfa.AddSymbol('1');

  nfa.SetStartState("q0");
  nfa.AddAcceptState("q1");

  nfa.AddTransition("q0", '1', {"q1"});

  CHECK(nfa.Prepare());

  CHECK(nfa.Accepts("1") == true);

  CHECK(nfa.Accepts("0") == false);
  CHECK(nfa.Accepts("10") == false);
  CHECK(nfa.Accepts("11") == false);
}
