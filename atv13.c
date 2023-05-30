#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 500000000

float *gerar_vetor(int n);
int *gerar_vetor_binario(int n);

int main() {
    MPI_Init(NULL, NULL);
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL) * rank);
    
    double inicio, fim;
    if (rank == 0) {
        inicio = MPI_Wtime();
    }

    int elementos_por_processo = TOTAL / num_procs;
    int *subvetor_binario = gerar_vetor_binario(elementos_por_processo);
    int cont_parcial = 0;

    for (int i = 0; i < elementos_por_processo; i++) {
        if (subvetor_binario[i] == 1) {
            cont_parcial++;
        }
    }

    int cont_total;
    MPI_Reduce(&cont_parcial, &cont_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        fim = MPI_Wtime();

        if (cont_total % 2 == 0) {
            printf("Adicionando um 0 ao arquivo (%d)...\n", cont_total);
        } else {
            printf("Adicionando um 1 ao arquivo (%d)...\n", cont_total);
        }

        printf("Tempo: %.2f\n", fim - inicio);
    }

    MPI_Finalize();
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor = (float *)malloc(sizeof(float) * n);

    for (int i = 0; i < n; i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }

    return vetor;
}

int *gerar_vetor_binario(int n) {
    int *vetor = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        int num = rand() % 2;
        vetor[i] = num;
    }

    return vetor;
}






