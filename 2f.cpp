#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int num_steps = 10000;
    double aux, pi;
    double step = 1.0 / (double)num_steps;
    double x = 0.0;
    double sum = 0.0;

    #pragma omp parallel private(x, aux)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            aux = 4.0 / (1.0 + x * x);

            #pragma omp critical
            {
                sum = sum + aux;
            }
        }
    }

    pi = step * sum;

    cout << "The Value of PI is " << pi << endl;

    return 0;
}