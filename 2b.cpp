#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int i = 0;
    volatile int x = 0; 
    omp_set_num_threads(5);

    #pragma omp parallel shared(i, x)
    {
        if (omp_get_thread_num() == 0) {
            #pragma omp critical
            {
                cout << "Master thread with Thread ID:" << omp_get_thread_num() << "\n";
                cout << "Since it is the producer thread It is adding some data to be consumed by other consumer threads\n";
            }
            i += 10;
            x = 1; 
        } else {
            while (x == 0) {
                #pragma omp critical
                {
                    cout << "Waiting for buffer to be filled. Thread ID: " << omp_get_thread_num() << "\n";
                }
            }
            
            #pragma omp critical
            {
                if (i > 0) {
                    cout << "Data is consumed by Consumer with Thread ID: " << omp_get_thread_num() << "\n";
                    i -= 5;
                } else {
                    cout << "Could not find any data for thread ID: " << omp_get_thread_num() << "\n";
                }
            }
        }
    }
    
    return 0;
}