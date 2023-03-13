#include <iostream>

#include "matrix_fraction/matrix_fraction.h"

int main() {
    int mode = 0;
    std::cout << "Please enter the mode of operation" << std::endl;
    std::cout << "1. Calculate SLAE" << std::endl;
    std::cout << "2. Find all bases solution" << std::endl;
    std::cin >> mode;

    MatrixFractions new_matrix_frac(5, 6);
    new_matrix_frac.GetMatrix("../files/SLAE.txt");

    if (mode == 1) {
        new_matrix_frac.PrintMatrix();
        new_matrix_frac.ReduceMatrix();
        new_matrix_frac.PrintMatrix();

        if (new_matrix_frac.CalculateSLAE() != 2) {
            std::cout << "RESULT:" << std::endl << std::endl;
            new_matrix_frac.PrintResault();
        }
    } else if (mode == 2) {
        // new_matrix_frac.CheckAllPosibleBases();
        new_matrix_frac.PrintMatrix();
        new_matrix_frac.ReduceMatrix();
        new_matrix_frac.PrintMatrix();

        if (new_matrix_frac.CalculateSLAE() != 2) {
            std::cout << "RESULT:" << std::endl << std::endl;
            new_matrix_frac.PrintResault();
        }
        new_matrix_frac.PrintMatrix();

        new_matrix_frac.CheckAllPosibleBases();
        new_matrix_frac.PrintTransmitionMatrix();
        std::cout << std::endl;
        new_matrix_frac.BasesTransition();
    }

    return 0;
}