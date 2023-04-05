#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "epidemic.hpp"

std::ofstream fout("datiSIR.txt");

void LogtoTXT(const EpidemicSIR& sir) {
  // stampa i dati della simulazione su file .txt
  fout << "Giorno S I R \n";
  for (long unsigned int i = 0; i < sir.GetSvector().size(); i++) {
    fout << i << ' ' << sir.GetSvector()[i] << ' ' << sir.GetIvector()[i] << ' '
         << sir.GetRvector()[i] << '\n';
  }
};

void LogtoTerminal(const EpidemicSIR& sir) {
  // stampa dati su terminale
  for (long unsigned int i = 0; i < sir.GetSvector().size(); i++) {
    std::cout << i << ' ' << sir.GetSvector()[i] << ' ' << sir.GetIvector()[i]
              << ' ' << sir.GetRvector()[i] << '\n';
  }
};

void Print(const EpidemicSIR& sir) {
  int m;

  std::cout << "selezionare modalità di visualizzazione dati tra seguenti "
               "opzioni: \n";
  std::cout << "immetti 1 per visualizzare su terminale; \n"
            << "immetti 2 per esportare su file di testo; \n"
            << "immetti 3 per eseguire entrambe le precedenti; \n";
  std::cin >> m;

  if (m != 1 && m != 2 && m != 3)
    throw std::runtime_error("impossibile immettere valori diversi da 1, 2, 3");

  switch (m) {
    case 1:
      LogtoTerminal(sir);
      break;
    case 2:
      LogtoTXT(sir);
      break;
    case 3:
      LogtoTXT(sir);
      LogtoTerminal(sir);
      break;
  }
};
