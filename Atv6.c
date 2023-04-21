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
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    double *valores = NULL;
    int indice = 0;
    double maximo = 0;

    vetor = gerar_vetor_inteiro(TAMANHO);
    valores = gerar_vetor(TAMANHO);

    double inicio = omp_get_wtime();

    #pragma omp parallel for reduction(max:maximo)
    for (int i = 0; i < TAMANHO; i++) {
        if (valores[i] > maximo) {
            maximo = valores[i];
            indice = i;
        }
    }

    double fim = omp_get_wtime();

    printf("Maior valor: %f\n", maximo);
    printf("Índice do maior valor: %d\n", indice_maximo);
    printf("Tempo de execução: %f segundos\n", fim - inicio);

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

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}