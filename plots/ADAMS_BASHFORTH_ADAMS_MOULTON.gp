set datafile separator ","
set title "Distance between RK4 and DOPRI8"
set xlabel "time"
set ylabel "Distance"
set grid
plot 'data/distance_ADAMS_BASHFORTH_20_0.01_0.01_ADAMS_MOULTON_20_0.0005_0.01.csv' using 1:2 with linespoints

pause -1