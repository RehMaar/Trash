if (!exists("driver")) driver='png'
if (!exists("filename")) filename='stdev.png'
if (!exists("datasrc"))  datasrc='stdev.dat'
set style data linespoints
set xlabel "Vector length"
set ylabel "St. dev"
set key autotitle columnhead
set grid ytics mytics
set mytics 5
set terminal dumb
set output '/dev/null'
plot datasrc
MAX=(1 + floor(GPVAL_Y_MAX * 0.12)) * 10
set ytics -MAX,(MAX / 5),MAX
set yrange [-1 : MAX] noreverse nowriteback
set terminal driver
set output filename
plot datasrc using 1:2 title "Rounding type",\
     datasrc using 1:3 title "Cuting type",\
     datasrc using 1:4 title "CutInc type"

# vim: set ft=gnuplot:

