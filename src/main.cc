#include <iostream>

#include "matrix/matrix_oop.h"
#include "matrix_fraction/matrix_fraction.h"

int main() {
    MatrixFractions new_matrix_frac(3, 5);
    new_matrix_frac.GetMatrix("../files/SLAE_4.txt");
    new_matrix_frac.PrintMatrix();
    new_matrix_frac.ReduceMatrix();
    new_matrix_frac.PrintMatrix();

    if (new_matrix_frac.CalculateSLAE() != 2) {
        std::cout << "RESULT:" << std::endl << std::endl;
        new_matrix_frac.PrintResault();
    }

    return 0;
}