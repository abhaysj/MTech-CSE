#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int np, rank, ierr;
    ierr = MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int n1, n2;
    MPI_Status status;

    if (rank == 0) {
        printf("Enter the two numbers: \n");
        scanf("%d %d", &n1, &n2);

        for (int i = 1; i < np; i++) {
            MPI_Send(&n1, 1, MPI_INT, i, 100, MPI_COMM_WORLD);
            MPI_Send(&n2, 1, MPI_INT, i, 100, MPI_COMM_WORLD);
        }
    }
    else if (rank == 1) {
        MPI_Recv(&n1, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Recv(&n2, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        int n3 = n1 + n2;
        printf("Result of addition operation done by process %d is %d\n", rank, n3);
    }
    else if (rank == 2) {
        MPI_Recv(&n1, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Recv(&n2, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        int n3 = n1 - n2;
        printf("Result of subtraction operation done by process %d is %d\n", rank, n3);
    }
    else if (rank == 3) {
        MPI_Recv(&n1, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Recv(&n2, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        int n3 = n1 * n2;
        printf("Result of multiplication operation done by process %d is %d\n", rank, n3);
    }
    else {
        MPI_Recv(&n1, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Recv(&n2, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        if (n2 != 0) {
            int n3 = n1 / n2;
            printf("Result of division operation done by process %d is %d\n", rank, n3);
        } else {
            printf("Division by zero attempted by process %d!\n", rank);
        }
    }

    ierr = MPI_Finalize();
    return 0;
}
