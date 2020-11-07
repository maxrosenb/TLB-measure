#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {

    const int PAGESIZE = 8192;
    const long NUMPAGES = atoi(argv[1]);
    const long NUM_TRIALS = atoi(argv[2]);

    char *a = malloc ((long) PAGESIZE * NUMPAGES);

    for (int i = 0; i < NUMPAGES; i++) {
        long jump = (long) i * PAGESIZE;
        a[jump] += 1;
    }
        
    long total = 0;

    struct timeval c_start;
    struct timeval c_stop;

    gettimeofday(&c_start, 0);

    for (int i = 0; i < NUM_TRIALS; i++) {
        asm("");
        for (int j = 0; j < NUMPAGES; j++) {
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
    
    double time_per_access = total_time / (NUMPAGES);

    printf("%ld\t %f\t \n", NUMPAGES, time_per_access);
    

    free(a);

    return 0;

}