#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {

    int rank, size;
    int array[6];

    int inputNumber;
    int maxNumber;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 6) {

        if (rank == 0) {

            cout << "Enter 6 integers: ";

            for (int i = 0; i < 6; i++) {
                cin >> array[i];
            }
        }

        MPI_Bcast(array,6,MPI_INT,0,MPI_COMM_WORLD);

        inputNumber = array[rank];

        cout << "Process " << rank
             << " has value "
             << inputNumber << endl;

        MPI_Reduce(&inputNumber,&maxNumber,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);

        if (rank == 0) {
            cout << "Maximum value is: "
                 << maxNumber << endl;
        }
    }
    else {

        if (rank == 0) {
            cout << "Run the program with 6 processes."
                 << endl;
        }
    }

    MPI_Finalize();

    return 0;
}
