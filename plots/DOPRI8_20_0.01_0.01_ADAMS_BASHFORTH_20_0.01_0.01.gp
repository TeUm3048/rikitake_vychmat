set datafile separator ","
set title "Distance between DOPRI8\\_20\\_0.01\\_0.01 and ADAMS\\_BASHFORTH\\_20\\_0.01\\_0.01"
set xlabel "time"
set ylabel "Distance"
set grid
plot 'data/distance_DOPRI8_20_0.01_0.01_ADAMS_BASHFORTH_20_0.01_0.01.csv' using 1:2 with linespoints

pause -1
