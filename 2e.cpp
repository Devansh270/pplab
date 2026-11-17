#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int numberOfElements;
    int currentMax = -1;
    int arrayInput[10000];

    cout << "Enter the Number of Elements: ";
    cin >> numberOfElements;

    for (int iIterator = 0; iIterator < numberOfElements; iIterator++) {
        cin >> arrayInput[iIterator];
    }

    #pragma omp parallel for shared(currentMax)
    for (int iIterator = 0; iIterator < numberOfElements; iIterator++) {

        #pragma omp critical
        {
            if (arrayInput[iIterator] > currentMax) {
                currentMax = arrayInput[iIterator];
            }
        }
    }

    cout << "The Maximum Element is: " << currentMax << endl;

    return 0;
}