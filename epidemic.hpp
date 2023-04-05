#ifndef EPIDEMIC_H
#define EPIDEMIC_H

#include <iostream>
#include <vector>

struct EpidemicPar {
  double gamma_;  // probabilità di guarigione di una persona infetta
  double beta_;   // probabilità di infettarsi di una persona suscettibile
};

class EpidemicSIR {
 private:
  const int t_;  // numero di giorni di simulazione

  EpidemicPar par_;

  int S_;  // numero di persone che si possono infettare
  int I_;  // numero di persone infette
  int R_;  // numero di persone guarite o in isolamento, non possono né
           // infettarsi né infettare

  const int N_;  // numero di persone totali, dato da S + I + R
                 // deve conservarsi durante il processo

  std::vector<int> S_vector;
  std::vector<int> I_vector;
  std::vector<int> R_vector;

 public:
  EpidemicSIR(int, EpidemicPar, int, int, int);
  // costruttore del modello SIR, inizializza S R I e N gamma beta e t
  // controlla che le variabili usate abbiano valori accettabili

  // i getters ritornano i valori dei vari parametri della nostra simulazione
  EpidemicPar GetParameters() const { return par_; };
  int GetS() const { return S_; };
  int GetI() const { return I_; };
  int GetR() const { return R_; };
  int GetN() const { return N_; };
  std::vector<int> GetSvector() const { return S_vector; };
  std::vector<int> GetIvector() const { return I_vector; };
  std::vector<int> GetRvector() const { return R_vector; };

  void Log(int) const;
  // stampa a schermo i valori di S I R di un dato giorno

  void Evolve();
  // il metodo fa evolvere l'epidemia di un giorno
  // applico equazioni differenziali del modello SIR
  // poi trasformo i risultati ottenuti in valori interi
};

inline void SetPar(EpidemicPar& par) {
  std::cout << "immetti probablilità di contagio (beta): \n";
  std::cin >> par.beta_;
  std::cout << "immetti probablilità di guarigione (gamma): \n";
  std::cin >> par.gamma_;
};

inline void SetT(int& t) {
  std::cout << "immmetti durata simulazione (giorni) \n";
  std::cin >> t;
};

inline void SetSIR(int& s, int& i, int& r) {
  std::cout
      << "immetti nell'ordine numero di persone sane, infette e rimosse \n";
  std::cin >> s >> i >> r;
};

#endif