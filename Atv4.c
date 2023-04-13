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
    vetor = gerar_vetor_inteiro(TAMANHO);


    double inicio = omp_get_wtime();

    int soma = 0;
    int i = 0;
    int num = 100000000;
    for(i = 1; i < num; i++) {
        if((num % i) == 0) {
            soma = soma + i;
        }
    }
    double fim = omp_get_wtime();
    double t_serial = fim-inicio;
    printf("soma dos divisores igual à %d", soma);
    printf("\nExecucao sequencial(s): %f\n",t_serial); 



    double inicio2 = omp_get_wtime();

    soma = 0;

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:soma)
            for(i = 1; i < num; i++) {
                if((num % i) == 0) {
                    soma += i;
                }
            }
    }

    double fim2 = omp_get_wtime();
    double t_serial1 = fim2-inicio2;
    printf("soma dos divisores igual à %d", soma);
    printf("\nExecucao paralela(s): %f\n",t_serial1);

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