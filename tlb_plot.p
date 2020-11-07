set terminal png
set output "tlb.png"

set style line 1 lt 1 lw 3 pt 3 linecolor rgb "red"

set title "TLB Size Measurement"

set xlabel "Number of Pages"

set ylabel "Time per Access (us)"

set logscale x 2

plot "tlb.dat" with linespoints lt rgb "orange"