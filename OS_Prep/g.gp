set title 'SSTF Disk Scheduling'
set xlabel 'Track'
set ylabel 'Order'
set xrange [10:20]
set yrange [-1:5]
plot '-' using 1:2 with linespoints pt 7
11 0
9 1
8 2
7 3
6 4
e
pause mouse close
