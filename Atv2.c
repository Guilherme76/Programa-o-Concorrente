#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

double *gerar_vetor(int n);
void mostrar_vetor(float *v,int tamanho);

int main() {
    int MAX = 100000000;
    time_t t;
    srand(time(NULL));
    double *vetor = NULL;
    vetor = gerar_vetor(MAX);
    int i;
    double soma_seq = 0.0;
    double soma_par = 0.0;
    double inicio,fim;

    // Cálculo sequencial da média aritmética
    inicio = omp_get_wtime();
    for (i=0;i<MAX;i++) {
        soma_seq += vetor[i];
    }
    double media_seq = soma_seq / (double)MAX;
    fim = omp_get_wtime();
    double tempo_seq = fim - inicio;

    // Cálculo paralelo da média aritmética
    inicio = omp_get_wtime();
    #pragma omp parallel for num_threads(3) reduction(+: soma_par)
    for (i=0;i<MAX;i++) {
        soma_par += vetor[i];
    }
    double media_par = soma_par / (double)MAX;
    fim = omp_get_wtime();
    double tempo_par = fim - inicio;

    // Impressão dos resultados
    printf("Soma sequencial: %lf\n", soma_seq);
    printf("Média sequencial: %lf\n", media_seq);
    printf("Tempo sequencial: %lf\n", tempo_seq);
    printf("\n");
    printf("Soma paralela: %lf\n", soma_par);
    printf("Média paralela: %lf\n", media_par);
    printf("Tempo paralelo: %lf\n", tempo_par);
    printf("\n");
    printf("Speedup: %lf\n", tempo_seq / tempo_par);
    printf("Eficiência: %lf\n", (tempo_seq / tempo_par) / 3.0);

    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (double)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}