set datafile separator ","
set title "Distance between DOPRI54\\_20\\_a0.001\\_r1e-11\\_0.01 and ADAMS\\_MOULTON\\_20\\_0.01\\_0.01"
set xlabel "time"
set ylabel "Distance"
set grid
plot 'data/distance_DOPRI54_20_a0.001_r1e-11_0.01_ADAMS_MOULTON_20_0.01_0.01.csv' using 1:2 with linespoints

pause -1
