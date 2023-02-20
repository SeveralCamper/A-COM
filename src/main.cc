#include <iostream>

#include "matrix/matrix_oop.h"
#include "matrix_fraction/matrix_fraction.h"

int main() {
    MatrixFractions new_matrix_frac(5, 6);
    new_matrix_frac.GetMatrix("../files/SLAE_1.txt");
    new_matrix_frac.PrintMatrix();
    new_matrix_frac.ReduceMatrix();
    new_matrix_frac.PrintMatrix();

    new_matrix_frac.CalculateSLAE();

    return 0;
}