set terminal png size 800, 600 crop;
set output "SIRmodel.png";
set title "Modello SIR"
set xlabel "Tempo (Giorni)"
set ylabel "Popolazione"
set grid
plot "datiSIR.txt" u 1:2 w lp lw 2 t "Suscettibili","datiSIR.txt" u 1:3 w lp lw 2 t "Infetti","datiSIR.txt" u 1:4 w lp lw 2 t "Rimossi"