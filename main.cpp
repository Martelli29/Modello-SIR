#include <fstream>
#include <iostream>

#include "epidemic.hpp"
#include "printing.hpp"

int main() {
  int t = 0;
  int S = 0;
  int I = 0;
  int R = 0;
  EpidemicPar gb = {0, 0};
  SetPar(gb);
  SetT(t);
  SetSIR(S, I, R);

  EpidemicSIR sir_(t, gb, S, I, R);
  sir_.Evolve();

  Print(sir_);
}
