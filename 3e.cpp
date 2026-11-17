#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {

    int rank, size;
    int value, sum = 0;

    int source, destination;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {

        destination = 1;

        MPI_Send(&rank,1,MPI_INT,destination,0,MPI_COMM_WORLD);
    }

    else if (rank < size - 1) {

        source = rank - 1;
        destination = rank + 1;

        MPI_Recv(&value,1,MPI_INT,source,0,MPI_COMM_WORLD,&status);

        sum = rank + value;

        MPI_Send(&sum,1,MPI_INT,destination,0,MPI_COMM_WORLD);
    }

    else {

        source = rank - 1;

        MPI_Recv(&value,1,MPI_INT,source,0,MPI_COMM_WORLD,&status);

        sum = rank + value;

        MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    if (rank == 0) {

        MPI_Recv(&sum,1,MPI_INT,size - 1,0,MPI_COMM_WORLD,&status);

        cout << "MyRank " << rank<< " Final SUM " << sum << endl;
    }

    MPI_Finalize();

    return 0;
}
