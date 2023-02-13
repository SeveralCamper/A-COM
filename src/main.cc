#include <iostream>

#include "matrix/matrix_oop.h"

int main() {
    int  model = 0;
    std::cout << "Please, enter program view model:" << std::endl;
    std::cout << "1. Simple fractions." << std::endl;
    std::cout << "2. Double." << std::endl;

    std::cin >> model;

    /* SimpleFractions frac(4, 7);
    SimpleFractions frac_2(2, 5);
    frac.printSimpleFraction();
    std::cout << std::endl;

    frac /= frac_2;
    frac.ReduceFraction();
    frac.printSimpleFraction();
    SimpleFractions frac_3(3.5);
    frac_2 = frac_2 - frac * frac_3;
    frac_2.printSimpleFraction(); */

    Matrix new_matrix(3,5);
    new_matrix.GetMatrix("../files/SLAE_3.txt");
    new_matrix.PrintMatrix();

    if (model == 1) {
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
    }

    return 0;
}