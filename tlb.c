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
    struct timeval t1;
    struct timeval t2;

    // Intialize memory used to store pages via malloc
    char *a = malloc ((long) PAGE_SIZE * NUM_PAGES);

    // Page allocation
    for (int i = 0; i < NUM_PAGES; i++) {
        long jump = (long) i * PAGE_SIZE;
        // Allocate each page
        a[jump] += 1;
    }

    // Need something to actually use each page access for
    long total = 0;

    gettimeofday(&t1, 0);

    for (int i = 0; i < NUM_TRIALS; i++) {
        // Empty asm is to prevent any compiler tricks
        asm("");
        for (int j = 0; j < NUM_PAGES; j++) {
            asm("");
                // Access a page
                long jump = (long) j * PAGE_SIZE;
                total += a[jump];
        }
    }
    
    gettimeofday(&t2, 0);

    const long time_start = t1.tv_usec;
    const long time_stop = t2.tv_usec;

    // Simple arithmetic to measure access time
    const double duration = ((double) (time_stop - time_start)); 

    const double time_per_access_ns = duration / (NUM_PAGES) / (NUM_TRIALS) * 1000;

    printf("%ld\t %f\t \n", NUM_PAGES, time_per_access_ns);
    
    free(a);
    
    return 0;

}