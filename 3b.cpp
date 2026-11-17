#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    int n, rank, size;

    double PI25DT = 3.14159265358979323846;
    double mypi, pi, h, sum, x;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    while (true) {

        if (rank == 0) {
            cout << "Enter the number of intervals: ";
            cin >> n;
        }

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (n == 0)
            break;

        h = 1.0 / n;
        sum = 0.0;

        for (int i = rank + 1; i <= n; i += size) {
            x = h * (i - 0.5);
            sum += 4.0 / (1.0 + x * x);
        }

        mypi = h * sum;

        MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

        if (rank == 0) {
            cout << "Pi is approximately " << pi << endl;
            cout << "Error is "
                 << fabs(pi - PI25DT) << endl;
        }
    }

    MPI_Finalize();

    return 0;
}
