#include "epidemic.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <vector>

EpidemicSIR::EpidemicSIR(int t, EpidemicPar par, int s, int i, int r)
    // costruttore del modello SIR, inizializza S R I e N gamma beta e t
    // controlla che le variabili usate abbiano valori accettabili
    : t_(t), par_(par), S_(s), I_(i), R_(r), N_(S_ + I_ + R_) {
  if (t <= 0) {
    throw std::runtime_error(
        "la simulazione non può avvenire con tempi minori o uguali a zero");
  }

  if (par_.beta_ < 0 || par_.beta_ > 1) {
    throw std::runtime_error(
        "il parametro beta deve essere compreso tra zero e uno");
  }

  if (par_.gamma_ < 0 || par_.gamma_ > 1) {
    throw std::runtime_error(
        "il parametro gamma deve essere compreso tra zero e uno");
  }

  if (S_ < 0 || I_ < 0 || R_ < 0) {
    throw std::runtime_error(
        "impossibile avere un numero negativo di persone infette, sane o "
        "guarite");
  }

  if (N_ == 0) {
    throw std::runtime_error(
        "Il numero di persone totali deve essere positivo");
  }
};


void EpidemicSIR::Evolve() {
  // il metodo fa evolvere l'epidemia di un giorno
  // applico equazioni differenziali del modello SIR
  // poi trasformo i risultati ottenuti in valori interi
  S_vector.push_back(S_);
  I_vector.push_back(I_);
  R_vector.push_back(R_);

  double delta_s;
  double delta_i;
  double delta_r;

  double db_s = S_;
  double db_i = I_;
  double db_r = R_;

  double decimal_s;
  double decimal_i;
  double decimal_r;

  for (int i = 1; i < t_; ++i) {
    // calcolo il cambiamento delle variabili dopo un giorno
    delta_s = ((-par_.beta_) * db_s * db_i) / N_;
    delta_i = ((par_.beta_ * db_s * db_i / N_) - par_.gamma_ * db_i);
    delta_r = par_.gamma_ * db_i;

    // calcolo le nuove variabili S I R
    db_s += delta_s;
    db_i += delta_i;
    db_r += delta_r;

    // trasformo i valori ottenuti in parte intera e parte decimale
    // assegno parte intera a variabili di S I R originali
    S_ = db_s;
    I_ = db_i;
    R_ = db_r;
    // assegno parte decimale a apposite variabili
    decimal_s = db_s - S_;
    decimal_i = db_i - I_;
    decimal_r = db_r - R_;

    // il calcolo di S I R non conserva il valora di N
    // approssima per difetto i valori nella conversione a int
    // distribuisco valori restanti tra S I R in base alla parte decimale
    int A = S_ + I_ + R_;
    while (A < N_) {
      if ((decimal_s > decimal_i) & (decimal_s > decimal_r)) {
        S_++;
        decimal_s = 0;
      } else if ((decimal_i > decimal_s) & (decimal_i > decimal_r)) {
        I_++;
        decimal_i = 0;
      } else {
        // se non c'è valore più alto degli altri aumento R
        R_++;
        decimal_r = 0;
      }
      A++;
    }

    assert(S_ + I_ + R_ == N_);
    assert(S_ <= S_vector[i - 1]);

    S_vector.push_back(S_);
    I_vector.push_back(I_);
    R_vector.push_back(R_);
  }
};