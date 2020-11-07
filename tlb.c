#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

// A simple program to measure the number of 8192 byte pages 
// that can fit into my 2015 MacBook Pro's Translation Lookaside Buffer (TLB).
// Apparently this is between 512 and 1024 8192 byte pages.
int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("Not enough arguments. Aborting.\n");
        return 1;
    }

    // Initialize experiment constants
    const long PAGE_SIZE = 8192;
    const long NUM_PAGES = atoi(argv[1]);
    const long NUM_TRIALS = atoi(argv[2]);

    // Initialize start and stop times
    struct timeval c_start;
    struct timeval c_stop;

    char *a = malloc ((long) PAGE_SIZE * NUM_PAGES);

    // Page allocation
    for (int i = 0; i < NUM_PAGES; i++) {
        long jump = (long) i * PAGE_SIZE;
        // Allocate each page
        a[jump] += 1;
    }

    // Need something to actually use each page reference for
    long total = 0;

    gettimeofday(&c_start, 0);

    for (int i = 0; i < NUM_TRIALS; i++) {
        // Empty asm is to prevent any compiler tricks
        asm("");
        for (int j = 0; j < NUM_PAGES; j++) {
            asm("");
                // Reference a page
                long jump = (long) j * PAGE_SIZE;
                total += a[jump];
        }
    }
    
    gettimeofday(&c_stop, 0);

    double time_start = c_start.tv_usec;
    double time_stop = c_stop.tv_usec;


    // Simple arithmetic to measure access time
    double duration;
    duration = ((double) (time_stop - time_start));

    double time_per_access = duration / (NUM_PAGES);

    printf("%ld\t %f\t \n", NUM_PAGES, time_per_access);
    
    free(a);
    
    return 0;

}