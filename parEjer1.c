#include <stdio.h>
#include <time.h>
#include <omp.h>

long num_steps = 10000000;
double step = 1.0/10000000.0;

int main(){

    int i;
    double x, pi, sum = 0.0;

    clock_t start_time, end_time;
    start_time = clock();

    #pragma omp parallel for private(x) reduction(+:sum)
    for(i=0; i<num_steps; ++i){
        x = (i - 0.5) * step;      
        sum += 4.0/(1.0+x*x);
    }

    pi = step * sum;

    end_time = clock();

    double total_time = ((double)(end_time - start_time))/CLOCKS_PER_SEC;
    printf( "PI value = %f\n", pi );
    printf( "Total time = %f seconds\n", total_time );

    return 0;
}
