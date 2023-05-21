#include <iostream>

#include "matrix_fraction/matrix_fraction.h"

int main() {
  int mode = 0;
  std::cout << "Please enter the mode of operation" << std::endl;
  std::cout << "1. Calculate SLAE" << std::endl;
  std::cout << "2. Find all bases solution" << std::endl;
  std::cout << "3. Solve transport task" << std::endl;
  std::cin >> mode;

  if (mode == 3) {
    MatrixFractions new_matrix_transport(2, 5);
    new_matrix_transport.GetTransportMatrix("../files/transport_task_6.txt");
    new_matrix_transport.TransportTask();
  } else {
    MatrixFractions new_matrix_frac(4, 6);
    std::vector<int> current_basis = {1, 2, 3};
    new_matrix_frac.GetMatrix("../files/SLAE_BASIS_1.txt");

    if (mode == 1) {
      new_matrix_frac.PrintMatrix();
      new_matrix_frac.ReduceMatrix();
      new_matrix_frac.PrintMatrix();

      if (new_matrix_frac.CalculateSLAE() != 2) {
        std::cout << "RESULT:" << std::endl << std::endl;
        new_matrix_frac.PrintResult(current_basis);
      }
    } else if (mode == 2) {
      // new_matrix_frac.CheckAllPosibleBases();
      new_matrix_frac.PrintMatrix();
      new_matrix_frac.ReduceMatrix();
      new_matrix_frac.PrintMatrix();

      if (new_matrix_frac.CalculateSLAE() != 2) {
        std::cout << "RESULT:" << std::endl << std::endl;
        new_matrix_frac.PrintResult(current_basis);
      }
      new_matrix_frac.PrintMatrix();

      new_matrix_frac.CheckAllPosibleBases();
      std::cout << std::endl;
      new_matrix_frac.BasesTransition();
    }
  }

  return 0;
}