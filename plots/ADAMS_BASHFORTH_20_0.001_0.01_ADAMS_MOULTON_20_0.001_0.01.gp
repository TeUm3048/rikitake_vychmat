set datafile separator ","
set title "Distance between ADAMS\\_BASHFORTH\\_20\\_0.001\\_0.01 and ADAMS\\_MOULTON\\_20\\_0.001\\_0.01"
set xlabel "time"
set ylabel "Distance"
set grid
plot 'data/distance_ADAMS_BASHFORTH_20_0.001_0.01_ADAMS_MOULTON_20_0.001_0.01.csv' using 1:2 with linespoints

pause -1
