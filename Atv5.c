#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    int *vetor = NULL;
    int i, soma, x = 0;
    printf("Digite um valor para x: ");
    scanf("%d", &x);

    double inicio, fim, tempo_sequencial, tempo_paralelo;
    vetor = gerar_vetor_inteiro(TAMANHO);

    inicio = omp_get_wtime();
    printf("Código Sequencial: ");
    for (i = 0; i < TAMANHO; i++) {
        if (vetor[i] == x) {
            soma++;
        }
    }
    fim = omp_get_wtime();
    tempo_sequencial = fim - inicio;

    printf("Total de ocorrencias de %d: %d vezes\n", x, soma);
    printf("Tempo serial: %f segundos\n", tempo_sequencial);

    soma = 0;
    inicio = omp_get_wtime();
    printf("Código Paralelo: ");
    #pragma omp parallel for reduction(+:soma)
        for (i = 0; i < TAMANHO; i++) {
            if (vetor[i] == x) {
                soma++;
            }
        }
    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;

    printf("Total de ocorrencias de %d: %d vezes\n", x, soma);
    printf("Tempo paralelo: %f segundos\n", tempo_paralelo);

    free(vetor);

    /*
    FIM
    */
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}
void mostrar_vetor_inteiro(int *v, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("[%d]", v[i]);
    }
    printf("\n");
}