if (!exists("driver")) driver='png'
if (!exists("filename")) filename='stdev_w.png'
if (!exists("datasrc"))  datasrc='stdev_w.dat'
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
plot datasrc using 1:2 title "2-bit",\
     datasrc using 1:3 title "4-bit"

# vim: set ft=gnuplot:

