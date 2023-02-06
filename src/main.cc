#include <iostream>

#include "matrix/matrix_oop.h"

int main() {
    int  model = 0;
    std::cout << "Please, enter program view model:" << std::endl;
    std::cout << "1. Simple fractions." << std::endl;
    std::cout << "2. Double." << std::endl;

    std::cin >> model;

    Matrix new_matrix(5, 6);
    new_matrix.GetMatrix("../files/SLAE.txt");
    new_matrix.PrintMatrix();

    if (model == 1 || model == 2) {
        std::cout << std::endl;
        new_matrix.PrintSLAE(model);
        std::cout << std::endl << std::endl;;
        new_matrix.CalculateSLAE(model);
    } else {
        std::cout << "Invalid input! Please enter view model from 0 to 1" << std::endl;
        return 0;
    }

    return 0;
}