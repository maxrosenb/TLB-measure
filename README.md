# TLB-measure

### Max Rosenberg

The main part of this project is `tlb.c`, a C program to measure the number of 8192 byte pages that can fit into my 2015 MacBook Pro's Translation Lookaside Buffer (TLB). This number appears to be between 512 and 1024.

Take a look at the following graph to see how long an average page access takes as number of pages grows.

![tlb png](https://github.com/maxrosenb/TLB-measure/blob/main/tlb.png)

The code in `tlb.c` is commented to provide reasoning or explanation for some of the lines of code.


### Installation and Testing
To test the code, compile `tlb.c` with the makefile by running `make`. The code is simple enough that it will compile regardless of operating system. Then run `python3 run_tlb.py` and the program will print out the time per access for each number of pages created, which increases by powers of 2.
