#include <stdio.h>
#include <omp.h>
#include<time.h>


int main() {
    FILE *archivo;
    char caracter;
    int espacios = 0;
    clock_t start_time, finish_time;
    start_time = clock();

    archivo = fopen("prueba.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }

    #pragma omp parallel reduction(+:espacios)
    {
        while ((caracter = getc(archivo)) != EOF) {
            if (caracter == ' ') {

                printf("Espacio encontrado en el hilo: %d \n", omp_get_thread_num());
                espacios++;
            }
        }
    }
    
    fclose(archivo);
    finish_time = clock();

    double total_time = ((double)(finish_time - start_time))/CLOCKS_PER_SEC;

    printf("El archivo contiene %d espacios en blanco.\n", espacios);
    printf( "Tiempo que demoro = %f \n", total_time );

    return 0;
}
