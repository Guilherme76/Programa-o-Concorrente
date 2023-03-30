#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAMANHO 10000000

int vetor[TAMANHO];
int n;

int main() {
    int i;
    double inicio, fim;

    // Gerar vetor com 10.000.000 de elementos aleatórios
    srand(time(NULL));
    for (i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % 100;
    }

    // Pedir ao usuário um valor para procurar
    printf("Digite um valor para procurar no vetor: ");
    scanf("%d", &n);

    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for (i = 0; i < TAMANHO; i++) {
            if (vetor[i] == n) {
                printf("Thread[%d] ACHOU: %d na posição %d\n", omp_get_thread_num(), n, i);
            }
        }
    }
    fim = omp_get_wtime();

    printf("Tempo de execução: %f segundos\n", fim - inicio);
    return 0;
}