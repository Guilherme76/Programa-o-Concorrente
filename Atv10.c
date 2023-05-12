#include <mpi.h>
#include <stdio.h>

#define NINTERVALS 50000000

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int ncpus, meu_rank;
    double h, x, soma_local, soma_total, meupi, pi, inicio, fim;
    long int i;

    MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);

    inicio = MPI_Wtime();
    h = 1.0 / (double)NINTERVALS;
    soma_local = 0.0;
    for (i = meu_rank + 1; i <= NINTERVALS; i += ncpus) {
        x = h * ((double)i - 0.5);
        soma_local += f(x);
    }
    meupi = h * soma_local;

    MPI_Reduce(&meupi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (meu_rank == 0) {
        pi *= 4.0;
        fim = MPI_Wtime();
        printf("Valor de pi: %f\n", pi);
        printf("Tempo de execucao: %f\n", fim - inicio);
    }

    MPI_Finalize();
    return 0;
}