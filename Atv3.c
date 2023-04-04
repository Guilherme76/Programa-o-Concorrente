#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define num_steps 300000000

int main() {
    double step, pi, sum = 0.0;
    int i;
    double inicio, fim, t_parallel;

    // Execução sequencial
    inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    for (i = 0; i < num_steps; i++) {
        double x = (double) i * step;
        double term = 1.0 / (1.0 + x*x);
        sum += term;
    }
    pi = 4.0 * step * sum;
    fim = omp_get_wtime();
    t_parallel = fim - inicio;

    printf("Pi sequencial: %f\n", pi);
    printf("Tempo de execucao sequencial: %f s\n", t_parallel);

    // Execução paralela
    inicio = omp_get_wtime();
    sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
        double x = (double) i * step;
        double term = 1.0 / (1.0 + x*x);
        sum += term;
    }
    pi = 4.0 * step * sum;
    fim = omp_get_wtime();
    t_parallel = fim - inicio;

    printf("Pi paralelo: %f\n", pi);
    printf("Tempo de execucao paralelo: %f s\n", t_parallel);

    return 0;
}