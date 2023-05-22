#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "matrix_fraction/matrix_fraction.h"

int main(int argc, char *argv[]) {
  std::string file_path = "../files/ZLP_1.txt";
  std::vector<std::vector<SimpleFractions>> matrix = GetInput(file_path);
  std::cout << std::endl;

  std::cout << "Изначальные входные данные:" << std::endl;

  for (auto &row : matrix) {
    for (auto &i : row) {
      std::cout << i << "; ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Выделим Z-строку в отдельный вектор:" << std::endl;

  std::vector<SimpleFractions> zRow = matrix[0];
  for (int i = 1; i < zRow.size(); ++i) {
    zRow[i] = -zRow[i];
    std::cout <<  zRow[i] << ' ';
  }
  std::cout << std::endl;

  matrix.erase(matrix.begin());

  const int Nbegin = matrix[0].size() - 1;

  for (int row = 0; row < matrix.size(); ++row) {
    matrix[row].insert(matrix[row].begin(), matrix[row].back());
    matrix[row].erase(matrix[row].begin() + matrix[row].size() - 1);
  }

  std::cout << std::endl;
  std::cout << "Запишем изначальное СЛАУ в удобной форме для будущего составления расширенной симплекс-таблицы:" << std::endl;

  for (auto &row : matrix) {
    for (auto &x : row) {
      std::cout << x << "; ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Определим, могут ли быть базисными переменными какие-то и изначальных:" << std::endl;

  std::vector<int> basis(matrix.size(), -1);
  for (int column = 0; column < matrix[0].size(); ++column) {
    int base_var = -1;
    bool flag = true;
    for (int row = 0; row < matrix.size(); ++row) {
      if (matrix[row][column] != 0 && matrix[row][column] != 1) {
        flag = false;
        break;
      } else {
        if (matrix[row][column] == 1) {
          if (base_var == -1) {
            base_var = row;
          } else {
            flag = false;
            break;
          }
        }
      }
    }
    if (flag && base_var >= 0) {
      if (basis[base_var] == -1) {
        basis[base_var] = column;
      }
    }
  }

  for (auto &i : basis) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  std::vector<bool> extended_columns(matrix[0].size(), false);

  std::vector<SimpleFractions> mTask(matrix[0].size());

  for (int i = 0; i < basis.size(); ++i) {
    if (basis[i] != -1)
      continue;
    for (int row = 0; row < matrix.size(); ++row) {
      if (i == row)
        matrix[row].push_back(1);
      else
        matrix[row].push_back(0);
    }
    mTask.push_back(0);
    zRow.push_back(0);
    extended_columns.push_back(true);
    for (int j = 0; j < matrix[i].size() - 1; ++j) {
      mTask[j] = mTask[j] - matrix[i][j];
    }
    basis[i] = matrix[i].size() - 1;
  }

  for (int i = 0; i < matrix.size(); ++i) {
    if (basis[i] >= 0 && zRow[basis[i]] != 0) {
      int index = basis[i];
      for (int j = 0; j < zRow.size(); ++j) {
        if (j == index)
          continue;
        zRow[j] = zRow[j] - matrix[i][j] * zRow[index];
      }
      zRow[index] = 0;
    }
  }

  std::cout << std::endl;
  std::cout << "После введения искусственных переменных получаем новый базис:" << std::endl;

  for (auto &i : basis) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  basis.push_back(-1);
  basis.push_back(-1);

  matrix.push_back(zRow);
  matrix.push_back(mTask);

  std::cout << std::endl;
  std::cout << "Выразим сумму искуственных переменных из системы ограничений и запишем расширенную симплекс-таблицу:" << std::endl << std::endl;

  PrintTable(matrix, basis);

  matrix = SimplexMethod(matrix, basis, extended_columns);

  bool flag = true;
  for (int i = 0; i < extended_columns.size(); ++i) {
    if (extended_columns[i]) {
      for (int j = 0; j < basis.size(); ++j) {
        if (basis[j] == i) {
          flag = false;
          break;
        }
      }
    }
  }

  for (auto &col : matrix.back()) {
    if (col != 0) {
      flag = false;
      break;
    }
  }

  PrintTable(matrix, basis);

  if (flag) {
    std::cout << "Исходная задача совместна" << std::endl;
    matrix.erase(matrix.begin() + matrix.size() - 1);
    matrix = SimplexMethod(matrix, basis, extended_columns);
    PrintTable(matrix, basis);
    int quantity_of_solutions = -1;
    for (int i = 1; i < matrix[0].size(); ++i) {
      if (matrix.back()[i] < 0) {
        flag = false;
        break;
      } else if (matrix.back()[i] == 0) {
        bool in_basis = false;
        for (auto &x : basis) {
          if (x == i) {
            in_basis = true;
            break;
          }
        }
        if (!in_basis) {
          quantity_of_solutions = i;
        }
      }
    }

    if (flag) {
      std::cout << "Исходная задача совместна - имеет 1 или более решений" << std::endl;
      if (quantity_of_solutions >= 0) {
        std::cout << "Исходная задача имеет несколько решений" << std::endl;
        std::cout << "X1=(";
      } else
        std::cout << "X=(";
      std::vector<SimpleFractions> XSol(Nbegin);
      for (int i = 0; i < basis.size(); ++i) {
        if (basis[i] >= 0 && basis[i] <= Nbegin) {
          XSol[basis[i] - 1] = matrix[i][0];
        }
      }
      for (int i = 0; i < XSol.size(); ++i) {
        std::cout << XSol[i];
        if (i == XSol.size() - 1)
          continue;
        std::cout << ";";
      }
      std::cout << ")" << std::endl;
      if (quantity_of_solutions >= 0) {
        int colIndex = quantity_of_solutions;
        int rowIndex = -1;
        std::vector<SimpleFractions> CO(matrix.size());
        for (int i = 0; i < matrix.size() - 1; ++i) {
          if (matrix[i][colIndex] > 0) {
            CO[i] = matrix[i][0] / matrix[i][colIndex];
            if (rowIndex == -1 || CO[rowIndex] > CO[i]) {
              rowIndex = i;
            }
          }
        }
        PrintTable(matrix, basis, {}, CO, colIndex, rowIndex);
        basis[rowIndex] = colIndex;
        matrix = SquareMethod(matrix, rowIndex, colIndex);
        PrintTable(matrix, basis);
        std::vector<SimpleFractions> XSol2(Nbegin);
        std::cout << "X2=(";
        for (int i = 0; i < basis.size(); ++i) {
          if (basis[i] >= 0 && basis[i] <= Nbegin) {
            XSol2[basis[i] - 1] = matrix[i][0];
          }
        }
        for (int i = 0; i < XSol2.size(); ++i) {
          std::cout << XSol2[i];
          if (i == XSol.size() - 1)
            continue;
          std::cout << ";";
        }
        std::cout << ")" << std::endl;
        std::cout << "X=(";
        for (int i = 0; i < Nbegin; ++i) {
          std::cout << XSol[i];
          SimpleFractions val = XSol2[i] - XSol[i];
          if (val > 0)
            std::cout << " + ";
          else if (val < 0)
            std::cout << " - ";
          if (val != 0)
            std::cout << val.ABS_sf() << "L";
          if (i == XSol.size() - 1)
            continue;
          std::cout << ";";
        }
        std::cout << ")" << std::endl;
      }
      std::cout << "Z(X)=" << matrix.back()[0] << std::endl;

    } else {
      std::cout << "Исходная задача имеет бесконечное множество решений" << std::endl;
    }
  } else {
    std::cout << "Исходная задача несовместна - не имеет ни одного решения" << std::endl;
  }

  return 0;
}
