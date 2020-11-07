# TLB-measure

## Max Rosenberg

A simple program to measure the number of 8192 byte pages that can fit into my 2015 MacBook Pro's Translation Lookaside Buffer (TLB). This number appears to be around 512. Written as specified in the homework section of Chapter 19 - Paging: Faster Translations (TLBs), except
with a python script for running rather than bash.

Take a look at tlb.png to see how long an average page access took as number of pages grew. The code is commented to provide reasoning for some of the lines of code.

### Installation and Testing
To test the code, compile `tlb.c` with the makefile by running `make`. The code is simple enough that it will compile regardless of operating system. Then run `python3 run_tlb.py` and the program will print out the time per access for each number of pages created, which increases by powers of 2.
