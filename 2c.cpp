#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    int m, n, p;
    cout << "Enter the number of rows in Matrix 1: ";
    cin >> m;
    cout << "Enter the number of columns in Matrix 1: ";
    cin >> n;
    vector<vector<int>> matrixA(m, vector<int>(n));
    cout << "<--Now Input the values for matrix 1 row-wise-->\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrixA[i][j];
        }
    }
    cout << "Enter the number of columns in Matrix 2: ";
    cin >> p;
    vector<vector<int>> matrixB(n, vector<int>(p));
    cout << "<--Now Input the values for matrix 2 row-wise-->\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            cin >> matrixB[i][j];
        }
    }
    vector<vector<int>> matrixC(m, vector<int>(p, 0));
    int i, j, k;
    #pragma omp parallel private(i, j, k) shared(matrixA, matrixB, matrixC)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < m; i = i + 1) {
            for (j = 0; j < p; j = j + 1) {
                matrixC[i][j] = 0;
                for (k = 0; k < n; k = k + 1) {
                    matrixC[i][j] = matrixC[i][j] + (matrixA[i][k] * matrixB[k][j]);
                }
            }
        }
    }
    cout << "The output after Matrix Multiplication is:\n";
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < p; c++) {
            cout << matrixC[r][c] << "\t";
        }
        cout << "\n";
    }   
    return 0;
}