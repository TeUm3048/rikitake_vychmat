set datafile separator ","
set title "Distance between RK4 and DOPRI8"
set xlabel "time"
set ylabel "Distance"
set grid
plot 'data/distance_DOPRI54_20_a1e-08_r1e-05_0.01_DOPRI8_20_0.01_0.01.csv' using 1:2 with linespoints

pause -1