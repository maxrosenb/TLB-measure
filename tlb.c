#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {

    const int PAGESIZE = 8192;
    const long NUM_PAGES = atoi(argv[1]);
    const long NUM_TRIALS = atoi(argv[2]);

    char *a = malloc ((long) PAGESIZE * NUM_PAGES);


    // Allocation
    for (int i = 0; i < NUM_PAGES; i++) {
        long jump = (long) i * PAGESIZE;
        // Allocate each page
        a[jump] += 1;
    }

    // Need something to use each reference to each page for    
    long total = 0;

    // Initialize start and stop times
    struct timeval c_start;
    struct timeval c_stop;

    gettimeofday(&c_start, 0);

    for (int i = 0; i < NUM_TRIALS; i++) {
        // Empty asm is to prevent any compiler tricks
        asm("");
        for (int j = 0; j < NUM_PAGES; j++) {
            asm("");
                long jump = (long) j * PAGESIZE;
                total += a[jump];
        }
    }
    
    gettimeofday(&c_stop, 0);

    double time_start = c_start.tv_usec;
    double time_stop = c_stop.tv_usec;
    
    double total_time;
    total_time = ((double) (time_stop - time_start));

    double time_per_access = total_time / (NUM_PAGES);

    printf("%ld\t %f\t \n", NUM_PAGES, time_per_access);
    
    free(a);
    
    return 0;

}