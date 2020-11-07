set terminal png

set output "tlb.png"

set title "TLB Size Measurement"

set logscale x 2

set xlabel "Number of Pages"

set ylabel "Time per Access (ns)"

plot "tlb.dat" with linespoints lt rgb "orange"