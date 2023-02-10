#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, q;
    int root = 0;
    int sarray[4];
    int rarray[4];
    int marray[4];
    for (int i = 0; i < 4; i++)
    {
        sarray[i] = 0;
        rarray[i] = 0;
        marray[i] = 0;
    }
    q = 4;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        for (int i = 0; i < 4; i++) sarray[i] = 200 + i * 10;
    }

    if (rank < q)
    {

        MPI_Scatter(sarray, 1, MPI_INT, rarray, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    printf(" Process [%d ] Send array %d %d %d %d \n", rank, sarray[0], sarray[1], sarray[2], sarray[3]);
    printf(" Process [%d ] Receive array %d %d %d %d \n", rank, rarray[0], rarray[1], rarray[2], rarray[3]);
    marray[0] = rarray[0] + rank * 2;
    printf(" Process [%d ] Modified array %d %d %d %d \n", rank, marray[0], marray[1], marray[2], marray[3]);
    MPI_Gather(marray, 1, MPI_INT, sarray, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Finalize();
    if (rank == 0)
    {
        printf(" Process [%d ] Gathered array %d %d %d %d \n", 0, sarray[0], sarray[1], sarray[2], sarray[3]);
    }
    return 0;
}
