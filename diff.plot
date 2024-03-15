# Первый график (двумерный)
set title "Rikitake 3D model"
set xlabel "t"
set grid
stats "< join rk4.data dopri8.data" name "A"

plot "< join rk4.data dopri8.data" using 1:($2 - $6) w lines t "x",\
     # "< join rk4.data dopri8.data" using 1:($3 -$7) w lines t "y",\
     # "< join rk4.data dopri8.data" using 1:($4 -$8) w lines t "z"


pause -1
