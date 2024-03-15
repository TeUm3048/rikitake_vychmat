# Первый график (двумерный)
set title "Rikitake 3D model"
set xlabel "t"
set grid

plot "data.txt" using 1:2 w lines t "x",\
     "data.txt" using 1:3 w lines t "y",\
     "data.txt" using 1:4 w lines t "z"


pause -1
