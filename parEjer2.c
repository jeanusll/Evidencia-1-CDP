#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
    long  int lim = 100000;
    int i, j, primo, prim_enc = 0;
    int numeros[lim + 1];
    clock_t start_time, finish_time;

    start_time = clock();
    
    #pragma omp parallel
    {
        for(i = 2; i <= lim; i++) {
            numeros[i] = 0;
        }

        #pragma omp for private(primo, j) reduction(+:prim_enc)
        for(i = 2; i <= lim; i++) {
            if(numeros[i] == 0) {
                primo = 1;

                for(j = 2; j * j <= i; j++) {
                    if(i % j == 0) {
                        primo = 0;
                        break;
                    }
                }

                if(primo) {
                    prim_enc++;
                    #pragma omp critical
                    printf("Numero primo encontrado: %d en el hilo %d\n", i, omp_get_thread_num());
                    
                    #pragma critical omp for schedule(static)
                    for(j = i * 2; j <= lim; j += i) {
                        numeros[j] = 1;
                    }
                }
            }
        }
    }

    printf("Hay %d numeros primos menores que %d\n", prim_enc, lim);
    finish_time = clock();

    double total_time = ((double)(finish_time - start_time)) / CLOCKS_PER_SEC;
    printf("Tiempo que demoro = %f \n", total_time);
    return 0;
}