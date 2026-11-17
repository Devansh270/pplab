#include <iostream>
#include <mpi.h>

using namespace std;

#define SIZE 4

int main(int argc, char* argv[]) {

    int rank, numtasks;

    char sendbuf[SIZE][SIZE] = {
        {'V', 'J', 'T', 'I'},
        {'V', 'J', 'T', 'I'},
        {'V', 'J', 'T', 'I'},
        {'V', 'J', 'T', 'I'}
    };

    char recvbuf[SIZE];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    if (numtasks == SIZE) {

        MPI_Scatter(sendbuf,SIZE,MPI_CHAR,recvbuf,SIZE,MPI_CHAR,0,MPI_COMM_WORLD);

        cout << "Rank = " << rank << " Result: ";

        for (int i = 0; i < SIZE; i++) {
            cout << recvbuf[i] << " ";
        }

        cout << endl;
    }
    else {

        if (rank == 0) {
            cout << "Must specify 4 processors." << endl;
        }
    }

    MPI_Finalize();

    return 0;
