#include <stdio.h>
#include<time.h>


int main(){

    int lim = 100000;
    int i, j, primo, prim_enc = 0;
    int numeros[lim+1]; 

    clock_t start_time, finish_time;
    start_time = clock();

    for(i = 0; i <= lim; i++){
        numeros[i] = 0;
    }   

    for(i = 2; i <= lim; i++){
        if(numeros[i] == 0){ 
            primo = 1; 
            for(j = 2; j < i; j++){                 
                if(i % j == 0){ 
                    primo = 0;                     
                    break; 
                }
            }
            
            if(primo){ 
                prim_enc++; 
                printf("Numero primo encontrado: %d\n", i);
                for(j = i * 2; j <= lim; j += i){ 
                    numeros[j] = 1;
                }
            }
        }
    }
    
    finish_time = clock();

    double total_time = ((double)(finish_time - start_time))/CLOCKS_PER_SEC;

    printf("Hay %d numeros primos menores que %d\n", prim_enc, lim);
    printf( "Tiempo que demoro = %f \n", total_time );

    return 0;
}