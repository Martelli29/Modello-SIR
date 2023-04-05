#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "epidemic.hpp"

#include "doctest.h"

TEST_CASE("Epidemic Model") {
  EpidemicPar par;
  par.gamma_ = 0.2;
  par.beta_ = 0.3;

  SUBCASE("Throw: t negativo") {
    CHECK_THROWS(EpidemicSIR(-3, par, 100, 3, 0));
  };

  SUBCASE("Throw: S negativo") {
    CHECK_THROWS(EpidemicSIR(10, par, -5, 100, 0));
  };

  SUBCASE("Throw: I negativo") {
    CHECK_THROWS(EpidemicSIR(10, par, 100, -5, 0));
  };

  SUBCASE("Throw: R negativo") {
    CHECK_THROWS(EpidemicSIR(10, par, 100, 10, -5));
  };

  SUBCASE("Throw: beta negativo") {
    par.beta_ = -0.2;
    CHECK_THROWS(EpidemicSIR(10, par, 100, 10, 0));
  };

  SUBCASE("Throw: gamma negativo") {
    par.gamma_ = -0.2;
    CHECK_THROWS(EpidemicSIR(10, par, 100, 10, 0));
  };

  SUBCASE("Throw: beta maggiore di 1") {
    par.beta_ = 2;
    CHECK_THROWS(EpidemicSIR(10, par, 100, 10, 0));
  };

  SUBCASE("Throw: gamma maggiore di 1") {
    par.gamma_ = 2;
    CHECK_THROWS(EpidemicSIR(10, par, 100, 10, 0));
  };

  SUBCASE("Throw: N uguale a 0") {
    CHECK_THROWS(EpidemicSIR(10, par, 0, 0, 0));
  };

  SUBCASE("Nominal: N conservato") {
    EpidemicSIR sir_test(15, par, 1000, 20, 0);
    sir_test.Evolve();
    CHECK(sir_test.GetN() ==
          sir_test.GetS() + sir_test.GetI() + sir_test.GetR());
  };

  SUBCASE("Nominal: S nullo, t = 2") {
    EpidemicSIR sir_test(2, par, 0, 100, 0);
    sir_test.Evolve();
    CHECK(sir_test.GetS() == 0);
    CHECK(sir_test.GetI() == 80);
    CHECK(sir_test.GetR() == 20);
  };

  SUBCASE("Nominal: I nullo") {
    EpidemicSIR sir_test(15, par, 100, 0, 10);
    sir_test.Evolve();
    CHECK(sir_test.GetS() == 100);
    CHECK(sir_test.GetI() == 0);
    CHECK(sir_test.GetR() == 10);
  };
}
