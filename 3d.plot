# Второй график (трехмерный)
set hidden3d
set grid
set xlabel "x"
set ylabel "y"
set zlabel "z"
set cblabel "time"
set style function pm3d

# Определяем градиентную палитру
set palette rgbformulae 7,5,15

# Считаем количество точек в файле
stats "data.txt" using 1 name "A" nooutput
set cbrange [A_min:A_max] 

splot "data.txt" using 2:3:4:1 with lines linecolor palette

pause -1
