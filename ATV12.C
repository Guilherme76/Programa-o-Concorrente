#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHO 10000
#define MAX  100

int gerar_numero_aleatorio(int max) {
    int num = (rand() % (max+1));
    return num;
}

int *gerar_vetor_aleatorio(int tamanho) {
    int *vetor = malloc(tamanho*sizeof(int));
    for (int i = 0; i < tamanho; i++) { 
        vetor[i] = gerar_numero_aleatorio(MAX);
    }
    return vetor;
}

double calcular_media(int *vetor, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return soma / (double)tamanho;
}

double calcular_desvio_padrao(int *vetor, int tamanho, double media) {
    double soma_dp = 0;
    for (int i = 0; i < tamanho; i++) {
        soma_dp += pow(vetor[i] - media, 2);
    }
    double soma_total;
    MPI_Allreduce(&soma_dp, &soma_total, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    return sqrt(soma_total / tamanho);
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand((unsigned)time(NULL) * rank);

    int subtamanho = TAMANHO / nprocs;
    int *subvetor = gerar_vetor_aleatorio(subtamanho);

    double media_local = calcular_media(subvetor, subtamanho);
    double media_global;
    MPI_Allreduce(&media_local, &media_global, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    double desvio_padrao = calcular_desvio_padrao(subvetor, subtamanho, media_global / nprocs);

    if (rank == 0) {
        printf("Desvio padrão: %f\n", desvio_padrao);
    }

    free(subvetor);
    MPI_Finalize();
    return 0;
}