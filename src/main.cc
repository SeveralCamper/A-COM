#include <iostream>

#include "matrix/matrix_oop.h"
#include "matrix_fraction/matrix_fraction.h"

int main() {
    int  model = 0;
    std::cout << "Please, enter program view model:" << std::endl;
    std::cout << "1. Simple fractions." << std::endl;
    std::cout << "2. Double." << std::endl;

    // std::cin >> model;

    Matrix new_matrix(3,5);
    new_matrix.GetMatrix("../files/SLAE_3.txt");
    new_matrix.PrintMatrix();

    double gap = 2.0;
    SimpleFractions gap_frac(gap);
    std::vector<SimpleFractions> vec;
    for (int i = 0; i < 5; i++) {
        vec.push_back(gap_frac);
    }

    for (int i = 0; i < 5; i++) {
        std::cout << std::endl;
        vec[i].PrintSimpleFraction();
        std::cout << std::endl;
    }

    /* MatrixFractions new_matrix_frac(5, 5);
    new_matrix_frac.GetMatrix("../files/SLAE.txt");
    new_matrix_frac.PrintMatrix();
    std::cout << "!" << std::endl;
    new_matrix_frac.ReduceMatrix();
    std::cout << "!" << std::endl;
    new_matrix_frac.PrintMatrix(); */

    /* if (model == 1) {
        std::cout << std::endl;
        new_matrix.PrintSLAE(model);
        std::cout << std::endl << std::endl;;
        new_matrix.CalculateSLAE(model);
    } else if (model == 2) {
        new_matrix.PrintSLAE(model);
        std::cout << std::endl << std::endl;;
        new_matrix.CalculateSLAE(model);
    } else {
        std::cout << "Invalid input! Please enter view model from 0 to 1" << std::endl;
    } */

    return 0;
}