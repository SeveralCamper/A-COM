#include <iostream>

#include "matrix/matrix_oop.h"

int main() {
    SimpleFractions frac(5, 2);
    frac.printSimpleFraction();
    std::cout << frac.convertToDouble() <<std::endl;
    SimpleFractions frac_2(123.456);
    frac_2.printSimpleFraction();
    std::cout << frac_2.convertToDouble() <<std::endl;

    Matrix new_matrix(5, 6);
    new_matrix.GetMatrix("../files/SLAE.txt");
    new_matrix.PrintMatrix();
    std::cout << std::endl;
    new_matrix.PrintSLAE();
    std::cout << std::endl << std::endl;;
    new_matrix.CalculateSLAE();

    return 0;
}